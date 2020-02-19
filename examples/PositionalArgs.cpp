#include <CommandLineInputParser/clip.hpp>
#include "ExampleUtils.hpp"

int main(int argc, char** argv, char** env)
{
	clip::utils::dumpRawInput(argc, argv, env);

	clip::CommandLineParser clp;

	clip::PositionalArgument posArg("debug");
	clp.addPositionalArgument(posArg);

	clp.addPositionalArgument({ "verbose" });
	
	clp.parse(argc, argv);

	clip::utils::dumpPositionalArgument(clp, posArg);
	clip::utils::dumpPositionalArgument(clp, "verbose");

	return 0;
} 