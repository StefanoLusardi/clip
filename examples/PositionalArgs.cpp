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
	
	return 0;

}

