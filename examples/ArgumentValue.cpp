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

	// -- clip::ArgumentValue<T> constructor is made private by design.
	//clip::ArgumentValue<std::string> argValue = clip::ArgumentValue<std::string>();			// This line will not compile.
	//clip::ArgumentValue<std::string>* argValue = new clip::ArgumentValue<std::string>();	// This line will not compile.

	// -- It is possible to create a clip::ArgumentValue<T> using the clip::value<T>() function.
	clip::ArgumentValue<std::string> argValue = clip::value<std::string>();

	// -- C++17 automatic template deduction in declaration.
	clip::ArgumentValue argValue = clip::value<int>();

	// -- Default argument value can be provided using clip::value<T>(t) override.
	clip::ArgumentValue argValue = clip::value<double>(3.14);

	// -- Fluent API to specify further options (set required options and override default value).
	clip::ArgumentValue argValue = clip::value<std::string>("initial_value").isRequired(true).value("some_value");

}