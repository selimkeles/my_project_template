# My Project

## Overview
This project is a template for setting up a cross-platform CMake-based development environment in Visual Studio Code. It is designed to be used as a starting point for building C/C++ projects on both Windows and Unix-like systems (Linux/macOS). The template includes a modular project structure, support for external libraries, and unit testing.

Use ```ChangeThis``` flag to change project specific stuff like Project Name, executables name since .vscode files do not forwards environment variables where every task performs on new shell. 

## Project Structure

The project is organized into the following directories:

```bash
my_project
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
│   └── bin
├── include
│   ├── .
│   ├── .
│   └── .
├── lib
│   ├── TaskScheduler
│   │   ├── LICENSE
│   │   ├── README
│   │   └── ...
│   .
│   .
│   .
├── src
│   ├── main.c
│   └── some_sub_folder2
│       ├── another_sub_folder2
│       │   └── subfile2.c
│       └── subfile1.c
└── tests
    └── test.c
```

- **include/**: Contains the header files (.h) for defining function prototypes, structures, and constants.
- **lib/**: Includes external libraries or third-party dependencies that the project might rely on.
- **src/**: Contains the source files (.c) that implement the functionality of the project.
- **tests/**: Includes the unit test files for testing the project’s functionality. These tests can be run to ensure that the implementation works correctly.

## Build Process

### Windows (MSVC)

On Windows, we use the **Windows Build Tools** toolchain for compiling the C source code. CMake will detect the platform and adjust the compilation flags accordingly. The project is built using `mcvs` on Windows.

### Unix-like Systems (Linux/macOS)

On Linux and macOS, the project can also be built using the same CMake approach. CMake will automatically detect the platform and use the appropriate compiler and flags.

## Build Instructions

### 1. Install Required Tools

- **Windows**: Install `Windows Build Tools` and `Ninja-Build`
- **Linux/macOS**: Ensure that you have `gcc`, `g++`, and `cmake` installed. You can install them using your package manager (e.g., `apt`, `brew`).

### 2. Building the Project

After installing the required tools, you can build the project by running `cmake` and `make` from the project root directory.

```bash
mkdir build
cd build
cmake ..
make
```
or
```
shortcut control+shift+p
type run task
select task:Build
```
Alternatively you can set default build and test task

This will compile the source code and generate an executable in the `build/` directory.

### 3. Other build options

```bash
# Create build directory
mkdir build
cd build

# Configure for Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build Debug
cmake --build .

# Configure for Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build Release
cmake --build .
```

### 4. Running Tests

You can run the unit tests with the following command:

```bash
ctest
```

This will compile and run the test files located in the `tests/` directory.

### 5. Cleaning the Build

To clean up the generated files and start from scratch, you can use the clean target:

```bash
make clean
```

This will remove the `build/` directory and all compiled files.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Feel free to fork this project, submit issues, or open pull requests if you have suggestions or improvements.