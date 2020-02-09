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

	// -- Specify a list of option names to be used during parsing to recognize this option
	clip::OptionalArgument optArg({ "a" });
	clip::OptionalArgument optArg({ "a", "option", "another-long-option", "too-much-options" });

	// -- Add an option description
	clip::OptionalArgument optArg({ "a", "option" }, "This is a brief option description");

	// -- Give the option a clip::ArgumentValue
	// -- Note that since clip::OptionalArgument<T> is a template class, when a clip::ArgumentValue is not given, the default T used is std::nullptr_t
	clip::OptionalArgument<std::string> optArg({ "a", "option" }, "Option Description", clip::value<std::string>("hello"));

	// -- C++17 automatic template deduction in declaration.
	clip::OptionalArgument optArg({ "a", "option" }, "Option Description", clip::value<std::string>("hello"));

	// -- Exploit clip::ArgumentValue fluent API to specify argument value directly inline.
	clip::OptionalArgument optArg({ "a", "option" }, "Option Description", clip::value<std::string>("hello").isRequired(true).value("some value"););

}