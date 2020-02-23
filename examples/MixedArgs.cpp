#include <CommandLineInputParser/clip.hpp>
#include "ExampleUtils.hpp"

int main(int argc, char** argv, char** env)
{
	clip::utils::dumpRawInput(argc, argv, env);

	clip::CommandLineParser clp;

	clip::OptionalArgument optA({ "a", "optional_a" }, "A description", clip::value<std::string>().isRequired(true));
	clp.addOptionalArgument(optA);

	clip::OptionalArgument optB({ "b", "optional_b" }, "B description", clip::value<std::string>().isRequired(true));
	clp.addOptionalArgument(optB);

	clip::PositionalArgument posC("positional_c");
	clp.addPositionalArgument(posC);
	
	clip::PositionalArgument posD("positional_d");
	clp.addPositionalArgument(posD);

	clp.parse(argc, argv);

	clip::utils::dumpOptionalArgument(clp, optA);
	clip::utils::dumpOptionalArgument(clp, optB);

	clip::utils::dumpPositionalArgument(clp, posC);
	clip::utils::dumpPositionalArgument(clp, posD);

	return 0;
}