#pragma once

#include "OptionalArgument.hpp"

#include <any>
#include <algorithm>
#include <string_view>

namespace clip
{
	using PositionalArgument = std::string;

	class CommandLineParser
	{
		class Match;

		struct PositionalArgumentParsed
		{
			PositionalArgumentParsed() { }
			PositionalArgumentParsed(std::string_view s) : name{ s } { }

			std::string name;
		};

		struct OptionalArgumentParsed
		{
			OptionalArgumentParsed() { }
			OptionalArgumentParsed(std::string_view s) : name{ s }, value{ std::nullopt } { }

			std::string name;
			std::optional<std::any> value;
		};

	public:
		explicit CommandLineParser() = default;
		~CommandLineParser() = default;

		CommandLineParser(const CommandLineParser&) = delete;
		CommandLineParser(CommandLineParser&&) noexcept = delete;
		CommandLineParser& operator=(const CommandLineParser&) = delete;
		CommandLineParser& operator=(CommandLineParser&&) noexcept = delete;

		void parse(int argc, char** argv);
		void setAppDescription() { }

		void showHelp() { }
		void showVersion() { }

		std::string appName() { }
		std::string appVersion() { }
		std::string appCompanyName() { }
		std::string appDescription() { }

		[[nodiscard]] auto getPositionalArgumentCount() const noexcept;
		void addPositionalArgument(const PositionalArgument& arg);
		void addPositionalArgument(PositionalArgument&& arg);
		bool isSet(PositionalArgument&& arg) const noexcept;
		bool isSet(const PositionalArgument& arg) const noexcept;

		[[nodiscard]] auto getOptionalArgumentCount() const noexcept;

		template <class T>
		void addOptionalArgument(const OptionalArgument<T>& opt)
		{
			std::any optValue = opt.getValue();
			OptionalArgument<std::any> optArg(opt.names(), opt.description(), clip::value<std::any>(std::move(optValue)));
			optionalArgs.push_back(std::move(optArg));
		}

		template <class T>
		void addOptionalArgument(OptionalArgument<T>&& opt)
		{
			std::any optValue = opt.getValue();
			OptionalArgument<std::any> optArg(opt.names(), opt.description(), clip::value<std::any>(std::move(optValue)));
			optionalArgs.push_back(std::move(optArg));
		}

		template <class T>
		bool isSet(const OptionalArgument<T>& opt)
		{
			return findOption(opt) != optionalArgs_Parsed.end();
		}

		template <class T>
		T getOptionValue(OptionalArgument<T>& opt)
		{
			if (const auto o = findOption(opt); o != optionalArgs_Parsed.end() && o->value.has_value())
				return std::any_cast<T>(o->value.value());

			return {};
		}

	private:
		std::string _exePath;
		std::vector<OptionalArgument<std::any>> optionalArgs;
		std::vector<PositionalArgument> positionalArgs;

		std::vector<OptionalArgumentParsed> optionalArgs_Parsed;
		std::vector<PositionalArgumentParsed> positionalArgs_Parsed;

	protected:
		void parseToken(std::string_view s);

		template <class T>
		auto findOption(const OptionalArgument<T>& opt) -> decltype(optionalArgs_Parsed)::iterator
		{
			return std::find_if(optionalArgs_Parsed.begin(), optionalArgs_Parsed.end(), [&opt](const auto arg)
			{
				auto names = opt.names();
				return std::any_of(names.begin(), names.end(), [&arg](const auto name)
				{
					return name == arg.name;
				});
			});
		}
	};

}
