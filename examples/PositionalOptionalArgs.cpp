#include <CommandLineInputParser/clip.hpp>
#include <iostream>


int main(int argc, char** argv, char** env)
{
	// Dump raw input
	{
		std::cout << "Executable path: " << argv[0] << "\n\n";
		std::cout << "Command Line Inputs: " << "\n";
		for (int i = 1; i < argc; ++i) { std::cout << argv[i] << std::endl; } std::cout << "\n\n";
		//while(*env) { std::cout << *env++ << std::endl; } std::cout << "\n\n";
	}

	clip::CommandLineParser clp;
	clip::PositionalArgument pos1("positional");
	clp.addPositionalArgument(pos1);
	clp.addPositionalArgument({ "another-positional" });

	clip::OptionalArgument optA({ "a", "a-short-option" }, "A description");

	clip::OptionalArgument optB1({ "b1-long-option" }, "B description", clip::value<int>());
	clip::OptionalArgument optB2({ "b2-long-option-only" });
	clip::OptionalArgument optB3({ "b3" });

	clip::OptionalArgument optC({ "c", "c-option" }, "C description", clip::value<std::string>().isRequired(true));
	clip::OptionalArgument optD({ "d", "constant" }, "Greek PI", clip::value<double>(3.14));

	clp.addOptionalArgument(optA);
	clp.addOptionalArgument(std::move(optC));
	clp.addOptionalArgument(std::move(optD));

	clp.parse(argc, argv);

	if (clp.isSet(pos1))
	{
		std::cout << "positional is set." << std::endl;
	}

	if (clp.isSet("another-positional"))
	{
		std::cout << "positional is set." << std::endl;
	}

	if (clp.isSet(optC))
	{
		std::cout << "opt C: set!" << std::endl;
		auto c = clp.getOptionValue(optC);
		std::cout << "Value: " << c << std::endl;
	}
	else
		std::cout << "opt C: NOT set" << std::endl;

	if (clp.isSet(optD))
	{
		std::cout << "opt D: set!" << std::endl;
		auto d = clp.getOptionValue(optD);
		std::cout << "Value: " << d << std::endl;
	}
	else
		std::cout << "opt D: NOT set" << std::endl;

	return 0;
}