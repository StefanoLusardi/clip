# clip

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c67464255ca74d61a2018f5abec9b764)](https://app.codacy.com/manual/StefanoLusardi/clip?utm_source=github.com&utm_medium=referral&utm_content=StefanoLusardi/clip&utm_campaign=Badge_Grade_Dashboard)
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

An extremely simple to use, yet fully fledged, C++ Command Line Parser library (compiled and single-header-only).

## Usage

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
*  Windows 10 - MSVC 16
*  Ubuntu 18.04 - GCC 9

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