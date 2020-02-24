#pragma once

#include "Api.hpp"
#include "OptionalArgument.hpp"

#include <algorithm>
#include <string_view>
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
	using PositionalArgument = std::string;

	class CLIP_API CommandLineParser
	{
		class Match;

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

		void parse(int argc, char** argv);

		//void setAppDescription() { }

		//void showHelp() { }
		//void showVersion() { }

		//std::string appName() { }
		//std::string appVersion() { }
		//std::string appCompanyName() { }
		//std::string appDescription() { }

		[[nodiscard]] size_t getPositionalArgumentCount() const noexcept;
		void addPositionalArgument(const PositionalArgument& arg);
		void addPositionalArgument(PositionalArgument&& arg);
		bool isSet(PositionalArgument&& arg) const noexcept;
		bool isSet(const PositionalArgument& arg) const noexcept;

		[[nodiscard]] size_t getOptionalArgumentCount() const noexcept;

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
		void parseToken(std::string_view s);

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
