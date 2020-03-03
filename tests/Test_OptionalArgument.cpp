#include "gtest/gtest.h"
#include <CommandLineInputParser/clip.hpp>

TEST(OptionalArgument, OptionalArgumentNameSingle2)
{
	const std::string argNames { "argname" };
	clip::OptionalArgument optArg({argNames});

	EXPECT_EQ(optArg.names().size(), 1);
	EXPECT_EQ(optArg.names().front(), argNames);
}

TEST(OptionalArgument, OptionalArgumentNameSingle1)
{
	const std::vector<std::string> argNames{ "argname" };
	clip::OptionalArgument optArg(argNames);

	EXPECT_EQ(optArg.names().size(), argNames.size());
	EXPECT_EQ(optArg.names().front(), argNames.at(0));
}

TEST(OptionalArgument, OptionalArgumentNameSingle)
{
	const std::vector<std::string> argNames{ "argname" };
	clip::OptionalArgument optArg(argNames);

	EXPECT_EQ(argNames, optArg.names());
}

TEST(OptionalArgument, OptionalArgumentNameMulti)
{
	const std::vector<std::string> argNames { "a, dashed-arg-name, underscores_arg_name" };
	clip::OptionalArgument optArg(argNames);

	EXPECT_EQ(argNames, optArg.names());
}

TEST(OptionalArgument, OptionalArgumentNameMissing)
{
	const std::vector<std::string> argNames{ };
	clip::OptionalArgument optArg(argNames);

	EXPECT_EQ(argNames, optArg.names());
}