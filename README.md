# clip
Linux: [![Build Status](https://stefanolusardi.visualstudio.com/clip/_apis/build/status/StefanoLusardi.clip?branchName=master&jobName=Linux1804_GCC9)](https://stefanolusardi.visualstudio.com/clip/_build/latest?definitionId=13&branchName=master)
Windows: [![Build Status](https://stefanolusardi.visualstudio.com/clip/_apis/build/status/StefanoLusardi.clip?branchName=master&jobName=Windows10_MSVC2019)](https://stefanolusardi.visualstudio.com/clip/_build/latest?definitionId=13&branchName=master)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c67464255ca74d61a2018f5abec9b764)](https://app.codacy.com/manual/StefanoLusardi/clip?utm_source=github.com&utm_medium=referral&utm_content=StefanoLusardi/clip&utm_campaign=Badge_Grade_Dashboard) 
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/dwyl/esta/issues) 
![GitHub](https://img.shields.io/github/license/stefanolusardi/clip) 
[![HitCount](http://hits.dwyl.com/stefanolusardi/clip.svg)](http://hits.dwyl.com/stefanolusardi/clip)

![GitHub top language](https://img.shields.io/github/languages/top/stefanolusardi/clip) 
![GitHub language count](https://img.shields.io/github/languages/count/stefanolusardi/clip) 
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/stefanolusardi/clip) 
![GitHub repo size](https://img.shields.io/github/repo-size/stefanolusardi/clip)

![GitHub last commit](https://img.shields.io/github/last-commit/stefanolusardi/clip) 
![GitHub release (latest by date)](https://img.shields.io/github/v/release/stefanolusardi/clip) 
![GitHub Release Date](https://img.shields.io/github/release-date/stefanolusardi/clip) 

An extremely simple to use, yet fully fledged, C++ Command Line Parser library (compiled and single-header-only).

## Integration

### Header-Only
Copy the single header file [clip.hpp](https://github.com/StefanoLusardi/clip/blob/master/single_header/CommandLineInputParser/clip.hpp) within your project and just use it.  
Requires a C++17 compiler.

### Compile
Building the library is the preferrable approach since it leads to faster compile and link times.  
Requires CMake (> 3.8) and a C++17 compiler.

```console
$ git clone https://github.com/stefanolusardi/clip.git
$ cd clip && mkdir build && cd build
$ cmake --build . --config Release
$ cmake --build . --config Debug
$ cmake --install . --prefix <ANYWHERE_YOU_LIKE>
```

## Platforms & Compilers
*   Windows 10 - MSVC 16
*   Ubuntu 18.04 - GCC 9

## Basic Usage
```cpp
// Create clip::CommandLineParser object
clip::CommandLineParser clp;

// Create and add clip::PositionalArgument
clip::PositionalArgument posArg("positional_arg");
clp.addPositionalArgument(posArg);

// Create and add clip::OptionalArgument
clip::OptionalArgument optArg({ "a", "a-opt", "a-opt-arg" }, "Opt Arg Description");
clp.addOptionalArgument(optArg);

// Create and add clip::OptionalArgument with:
// expected type (e.g. std::string), default value (e.g. "initial_value") and other options (e.g. isRequired)
clip::OptionalArgument optArgValue({ "c" }, "Description", clip::value<std::string>("initial_value").isRequired(true));
clp.addOptionalArgument(optArgValue);

// Invoke parse method
clp.parse(argc, argv);

if (clp.isSet(posArg))
{
    std::cout << "positional_arg is set." << std::endl;
}

if (clp.isSet(optArgValue))
{
    auto v = clp.getOptionValue(optArgValue);
    std::cout << "Value: " << v << std::endl;
}
```

## Argument Value Usage
```cpp
// -- clip::ArgumentValue<T> constructor is made private by design.
//clip::ArgumentValue<std::string> argValue = clip::ArgumentValue<std::string>();        // This line will not compile.
//clip::ArgumentValue<std::string>* argValue = new clip::ArgumentValue<std::string>();   // This line will not compile.

// -- It is possible to create a clip::ArgumentValue<T> using the clip::value<T>() function.
clip::ArgumentValue<std::string> argValue = clip::value<std::string>();

// -- C++17 automatic template deduction in declaration.
clip::ArgumentValue argValue = clip::value<int>();

// -- Default argument value can be provided using clip::value<T>(t) override.
clip::ArgumentValue argValue = clip::value<double>(3.14);

// -- Fluent API to specify further options (set required options and override default value).
clip::ArgumentValue argValue = clip::value<std::string>("initial_value").isRequired(true).value("some_value");
```

## Optional Argument Usage
```cpp
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
```

## Examples
Examples are located within the [examples](https://github.com/StefanoLusardi/clip/tree/master/examples) folder.  
It is possible to build all the examples using:
```console
$ git clone https://github.com/stefanolusardi/clip.git
$ cd clip && mkdir build && cd build
$ cmake --build . --config Release -DBUILD_EXAMPLES=ON
```

## Tests
Coming soon
