#pragma once

#include <CommandLineInputParser/clip.hpp>
#include <iostream>


namespace clip::utils
{
	inline void dumpRawInput(int argc, char** argv, char** env)
	{
		std::cout << "Executable path: " << argv[0] << "\n\n";
		std::cout << "Command Line Inputs: " << "\n";
		for (int i = 1; i < argc; ++i) { std::cout << argv[i] << std::endl; } std::cout << "\n\n";
		//while(*env) { std::cout << *env++ << std::endl; } std::cout << "\n\n";
	}

	template <class T>
	void dumpOptionalArgument(const clip::CommandLineParser& clp, const clip::OptionalArgument<T>& opt)
	{
		auto printNames = [](const auto& opt)
		{
			const auto names{ opt.names() };
			std::cout << "Option names: ";
			std::for_each(names.cbegin(), names.cend(), [](const auto& name) { std::cout << "-" << name << " "; });
		};

		if (clp.isSet(opt))
		{
			printNames(opt);
			std::cout << "\n" 
				<< "Description: " << opt.description() << "\n"
				<< "Has Default Value: " << std::boolalpha << opt.hasValue() << "\n"
				<< "Is Value Required: " << std::boolalpha << opt.isValueRequired() << "\n";

			if (const auto optValue = clp.getOptionValue(opt); optValue.has_value())
				std::cout << "Value: " << optValue.value() << "\n";
		}
		else
		{
			printNames(opt);
			std::cout << "is not set. " << "\n";
		}

		std::cout << "\n";
	};
}