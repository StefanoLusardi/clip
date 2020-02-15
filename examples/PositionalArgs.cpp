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

	if (clp.isSet(posArg))
	{
		//std::cout << "Positional arg " << posArg.name() << " (" << posArg.description() << ")" << " is set." << std::endl;
	}

	if (clp.isSet("verbose"))
	{
		std::cout << "positional is set." << std::endl;
	}

	return 0;
}