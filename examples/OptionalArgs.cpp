#include <CommandLineInputParser/clip.hpp>
#include "ExampleUtils.hpp"

int main(int argc, char** argv, char** env)
{
	clip::utils::dumpRawInput(argc, argv, env);

	clip::CommandLineParser clp;

	clip::OptionalArgument optA({ "a", "a_opt" });
	clip::OptionalArgument optB({ "b", "b_opt" }, "B description");
	clip::OptionalArgument optC({ "c", "c_opt" }, "C description", clip::value<double>(3.14));
	clip::OptionalArgument optD({ "d", "d_opt" }, "D description", clip::value<std::string>().isRequired(true));

	clp.addOptionalArgument(optA);
	clp.addOptionalArgument(optB);
	clp.addOptionalArgument(optC);
	clp.addOptionalArgument(optD);

	clp.parse(argc, argv);

	clip::utils::dumpOptionalArgument(clp, optA);
	clip::utils::dumpOptionalArgument(clp, optB);
	clip::utils::dumpOptionalArgument(clp, optC);
	clip::utils::dumpOptionalArgument(clp, optD);

	return 0;
}