#include "CommandLineInputParser/CommandLineParser.hpp"
#include "Match.hpp"

#include <regex>

#ifndef CLIP_COMPILED_LIB
#error Please define CLIP_COMPILED_LIB
#endif

namespace clip
{
	void CommandLineParser::parse(int argc, char** argv)
	{
		_exePath = std::string(argv[0]);

		for (int i = 1; i < argc; ++i)
		{
			parseToken(std::string_view(argv[i]));
		}
	}

	size_t CommandLineParser::getPositionalArgumentCount() const noexcept { return _posArgsDeclared.size(); }
	
	void CommandLineParser::addPositionalArgument(const PositionalArgument& arg) { _posArgsDeclared.emplace_back(arg); }
	
	void CommandLineParser::addPositionalArgument(PositionalArgument&& arg) { _posArgsDeclared.emplace_back(arg); }

	bool CommandLineParser::isSet(PositionalArgument&& arg) const noexcept
	{
		return std::any_of(_posArgsParsed.begin(), _posArgsParsed.end(), [arg](const PositionalArgumentParsed& a) { return arg == a.name; });
	}
	
	bool CommandLineParser::isSet(const PositionalArgument& arg) const noexcept
	{
		return std::any_of(_posArgsParsed.begin(), _posArgsParsed.end(), [arg](const PositionalArgumentParsed& a) { return arg == a.name; });
	}

	size_t CommandLineParser::getOptionalArgumentCount() const noexcept { return _optArgsParsed.size(); }

	void CommandLineParser::parseToken(std::string_view s)
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
							argParsed.parsedValue = isNumeric(v) ? std::any(std::stod(v)) : v;
							break;
					}
					match.next();
				}
			}
			_optArgsParsed.emplace_back(argParsed);
		}
	}
}