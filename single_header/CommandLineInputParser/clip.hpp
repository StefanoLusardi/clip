#pragma once

#include <utility>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>
#include <stdexcept>
#include <regex>
#include <iostream>

#if defined(__GNUC__)
/* 
** Workaround to fix GCC libstdc++ bug: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90415
** Proposed fix is based on: https://stackoverflow.com/questions/57332965/incomplete-type-for-stdany-when-gmocking-interface
** See also the same issue on Clang: https://stackoverflow.com/questions/54922619/type-trait-on-stdreference-wrapperstdany
*/
	#include <experimental/any>
	#define clip_any std::experimental::fundamentals_v1::any
	#define any_cast experimental::fundamentals_v1::any_cast
	#define bad_any_cast experimental::fundamentals_v1::bad_any_cast
#else
	#include <any>
	#define clip_any std::any
	#define any_cast any_cast
	#define bad_any_cast bad_any_cast
#endif

namespace clip
{

	template<class T>
	class ArgumentValue;

	template<class T>
	ArgumentValue<T> value()
	{
		return ArgumentValue<T>();
	}

	template<class T>
	ArgumentValue<T> value(T&& v)
	{
		return ArgumentValue<T>(std::forward<T>(v));
	}

	template <typename T>
	class ArgumentValue
	{
	public:
		ArgumentValue(const ArgumentValue&) = default;
		ArgumentValue(ArgumentValue&&) noexcept = default;

		ArgumentValue& operator=(const ArgumentValue&) = delete;
		ArgumentValue& operator=(ArgumentValue&&) noexcept = default;

		~ArgumentValue() { }

		bool isRequired() const { return _required; }
		ArgumentValue isRequired(bool required) { _required = required; return *this; }
		
		T defaultValue() const { return _v; }
		ArgumentValue defaultValue(const T& t) { _v = t; return *this; }

		friend ArgumentValue<T> clip::value<T>();
		friend ArgumentValue<T> clip::value<T>(T&& v);

	protected:
		explicit ArgumentValue() : _v{}, _required{ false } { }
		explicit ArgumentValue(T&& v) : _v{ v }, _required{ false } { }

	private:
		T _v;
		bool _required;
	};

	template <typename T = std::nullptr_t>
	class OptionalArgument
	{
	public:
		~OptionalArgument() = default;

		explicit OptionalArgument(const std::vector<std::string>& names)
			: _names{ names }
			, _argValue{ std::nullopt } { }

		explicit OptionalArgument(const std::vector<std::string>& names, const std::string& description)
			: _names{ names }
			, _description{ description }
			, _argValue{ std::nullopt } { }

		explicit OptionalArgument(const std::vector<std::string>& names, const std::string& description, ArgumentValue<T>&& value)
			: _names{ names }
			, _description{ description }
			, _argValue{ std::make_optional(value) } { }

		OptionalArgument(OptionalArgument&& other) noexcept
			: _names{ std::move(other._names) }
			, _description{ std::move(other._description) }
			, _argValue{ std::move(other._argValue) } { }

		std::vector<std::string> names() const noexcept { return _names; }
		
		std::string description() const noexcept { return _description; }
		
		[[nodiscard]] bool hasValue() const noexcept { return _argValue.has_value(); }

		[[nodiscard]] bool isValueRequired() const noexcept
		{ 
			if (!hasValue())
				return false; // considering to throw an exception
				
			return _argValue.value().isRequired();
		}

		T getValue() const noexcept
		{
			if (!hasValue())
				return {};

			return _argValue.value().defaultValue();
		}
	
	private:
		std::optional<ArgumentValue<T>> _argValue;
		std::vector<std::string> _names;
		std::string _description;
	};

	using PositionalArgument = std::string;
	class CommandLineParser
	{
		class Match
		{
		public:
			enum class Index { Full, Dash, Name, Equal, Value, SIZE };

			void next()
			{
				if (_index == Index::SIZE) { throw std::out_of_range("Match::Index next() has been called after Match::Index::SIZE"); }

				int idx = static_cast<int>(_index);
				_index = static_cast<Match::Index>(++idx);
			}

			Match::Index index() { return _index; }
			static int size() noexcept { return static_cast<int>(Match::Index::SIZE); }

		private:
			Match::Index _index = Match::Index::Full;
		};

		struct PositionalArgumentParsed
		{
			explicit PositionalArgumentParsed() { }
			explicit PositionalArgumentParsed(std::string_view s) : name{ s } { }

			std::string name;
		};

		struct OptionalArgumentParsed
		{
			explicit OptionalArgumentParsed() { }
			explicit OptionalArgumentParsed(std::string_view s) : name{ s }, parsedValue{ std::nullopt } { }

			std::string name;
			std::optional<clip_any> parsedValue;
		};

	public:
		explicit CommandLineParser() = default;
		~CommandLineParser() = default;
		CommandLineParser(const CommandLineParser&) = delete;
		CommandLineParser(CommandLineParser&&) noexcept = delete;
		CommandLineParser& operator=(const CommandLineParser&) = delete;
		CommandLineParser& operator=(CommandLineParser&&) noexcept = delete;

		void parse(int argc, char** argv)
		{
			_exePath = std::string(argv[0]);

			for (int i = 1; i < argc; ++i)
			{
				parseToken(std::string_view(argv[i]));
			}
		}

		[[nodiscard]] size_t getPositionalArgumentCount() const noexcept { return _posArgsDeclared.size(); }
		void addPositionalArgument(const PositionalArgument& arg) { _posArgsDeclared.emplace_back(arg); }
		void addPositionalArgument(PositionalArgument&& arg) { _posArgsDeclared.emplace_back(arg); }
		bool isSet(PositionalArgument&& arg) const noexcept
		{
			return std::any_of(_posArgsParsed.begin(), _posArgsParsed.end(), 
			[arg](const PositionalArgumentParsed& a) { return arg == a.name; });
		}
		bool isSet(const PositionalArgument& arg) const noexcept
		{
			return std::any_of(_posArgsParsed.begin(), _posArgsParsed.end(), 
			[arg](const PositionalArgumentParsed& a) { return arg == a.name; });
		}

		[[nodiscard]] size_t getOptionalArgumentCount() const noexcept { return _optArgsDeclared.size(); }

		template <class T>
		void addOptionalArgument(const OptionalArgument<T>& opt)
		{
			clip_any optValue = opt.getValue();
			OptionalArgument<clip_any> optArg(opt.names(), opt.description(), clip::value<clip_any>(std::move(optValue)));
			_optArgsDeclared.push_back(std::move(optArg));
		}

		template <class T>
		void addOptionalArgument(OptionalArgument<T>&& opt)
		{
			clip_any optValue = opt.getValue();
			OptionalArgument<clip_any> optArg(opt.names(), opt.description(), clip::value<clip_any>(std::move(optValue)));
			_optArgsDeclared.push_back(std::move(optArg));
		}

		template <class T>
		bool isSet(const OptionalArgument<T>& opt) const
		{
			return findOption(opt) != _optArgsParsed.end();
		}

		template <class T>
		std::optional<T> getOptionValue(const OptionalArgument<T>& opt) const
		{
			if (const auto o = findOption(opt); o != _optArgsParsed.end()
				&& o->parsedValue.has_value() // The parsed option actually holds a value
				&& opt.hasValue()) // The user has defined a value for this option
			{
				try
				{
					return std::any_cast<T>(o->parsedValue.value());
				}
				catch (const std::bad_any_cast & e)
				{
					std::cout << e.what() << "\n";
					std::cout << "Type mismatch. ArgumentValue type declared and parsed are incompatible."  << "\n";
				}
			}

			return std::nullopt;
		}

	protected:
		void parseToken(std::string_view s)
		{
			const auto isPositional = [](std::string_view s) -> bool
			{
				// If the token does not have "-" at index 0 then it's a positional argument
				return s.find_first_of("-") != 0;
			};

			if (isPositional(s))
			{
				_posArgsParsed.emplace_back(s);
				return;
			}

			auto isNumeric = [](const std::string& s)
			{
				// Check if the matched value is numeric in order to cast it to double instead of a string.
				const std::regex doubleRegex("^[0-9]+(.|,)?[0-9]*$");
				return std::regex_match(s, doubleRegex);
			};

			const std::string token = std::string(s);
			std::smatch matches;
			const std::regex r("^([-]{0,2})([a-zA-Z0-9_]+)([=]([a-zA-Z0-9_.]+)*){0,1}$");
			if (std::regex_match(token, matches, r))
			{
				// matches[0] = Match::Index::Full	^([-]{0,2})([a-zA-Z0-9_]+)([=]([a-zA-Z0-9_.]+)*){0,1}$
				// matches[1] = Match::Index::Dash	([-]{0,2})
				// matches[2] = Match::Index::Name	([a-zA-Z0-9_]+)
				// matches[3] = Match::Index::Equal	([=]([a-zA-Z0-9_.]+)*){0,1}
				// matches[4] = Match::Index::Value	([a-zA-Z0-9_.]+)*

				// 5 matches expected (Full + 4 sub-matches)
				if (matches.size() != Match::size())
					return;

				Match match;
				OptionalArgumentParsed argParsed;
				for (auto&& m : matches)
				{
					if (m.matched)
					{
						switch (match.index())
						{
							case Match::Index::Name:
								argParsed.name = m.str();
								break;

							case Match::Index::Value:
								const std::string v = m.str();
								argParsed.parsedValue = isNumeric(v) ? clip_any(std::stod(v)) : v;
								break;
						}
						match.next();
					}
				}
				_optArgsParsed.emplace_back(argParsed);
			}
		}

		template <class T>
		auto findOption(const OptionalArgument<T>& opt) const
		{
			return std::find_if(_optArgsParsed.begin(), _optArgsParsed.end(), [&opt](const auto arg)
			{
				auto names = opt.names();
				return std::any_of(names.begin(), names.end(), [&arg](const auto name)
				{
					return name == arg.name;
				});
			});
		}

	private:
		std::string _exePath;
		
		std::vector<OptionalArgument<clip_any>> _optArgsDeclared;
		std::vector<OptionalArgumentParsed> _optArgsParsed;

		std::vector<PositionalArgument> _posArgsDeclared;
		std::vector<PositionalArgumentParsed> _posArgsParsed;
	};

}