# My Project

## Overview

This project is a C-based software solution designed to provide functionality related to **cron expression parsing**. It demonstrates modular design by separating source files, headers, libraries, and tests. The project is designed to be cross-platform, supporting both Windows and Unix-like systems (Linux/macOS). It uses a **Makefile** to handle the build process, ensuring that the correct compiler is used for each platform.

## Project Structure

The project is organized into the following directories:

```bash
my_project/
├── LICENSE                     # License information for the project
├── README.md                   # This file - Project overview and setup instructions
├── makefile                    # Makefile
├── build                       # executables of the project
│   ├── test
│   ├── debug
│   └── release
│       └── Vx.x
├── include                     # Header files for the project
│   ├── ccronexpr.h
│   └── some_sub_folder
│       └── another_sub_folder
├── lib                         # External libraries used in the project
│   ├── 3rdpartyLib1
│   └── 3rdpartyLib2
├── src                         # Source files for the project
│   ├── ccronexpr.c
│   ├── some_sub_folder2
│   │   └── another_sub_folder2
│   └── supertinycron.c
└── tests                       # Unit tests for the project
    └── ccronexpr_test.c
```

- **include/**: Contains the header files (.h) for defining function prototypes, structures, and constants.
- **lib/**: Includes external libraries or third-party dependencies that the project might rely on.
- **src/**: Contains the source files (.c) that implement the functionality of the project.
- **tests/**: Includes the unit test files for testing the project’s functionality. These tests can be run to ensure that the implementation works correctly.

## Platform-Specific Build Process

### Windows (MinGW)

On Windows, we use the **MinGW** toolchain for compiling the C source code. A `Makefile` is included in the root directory to automate the build process. This `Makefile` detects the platform and adjusts the compilation flags accordingly. The project is built using `gcc` (MinGW) on Windows.

### Unix-like Systems (Linux/macOS)

On Linux and macOS, the project can also be built using the same `Makefile` approach. The `Makefile` will automatically detect the platform and use the appropriate compiler and flags.

## Build Instructions

### 1. Install Required Tools

- **Windows**: Install **MinGW** or **MSYS2** to get the GCC compiler.
- **Linux/macOS**: Ensure that you have `gcc` and `make` installed. You can install them using your package manager (e.g., `apt`, `brew`).

### 2. Building the Project

After installing the required tools, you can build the project by running `make` from the project root directory.

```bash
make
```
This will compile the source code and generate an executable in the Build/debug/ directory.
### 3. Running Tests

You can run the unit tests with the following command:

```bash
make test
```

This will compile and run the test files located in the tests/ directory.
### 4. Cleaning the Build

To clean up the generated files and start from scratch, you can use the clean target:

```bash
make clean
```

This will remove the Build/ directory and all compiled files.
Configuration for VSCode
Tasks

The project includes VSCode tasks for building, cleaning, and running tests. The tasks are configured to run the make command, which will invoke the Makefile. Here's how to use them:

 >  [Note]  
 >  Open the project in VSCode.
 >  Press Ctrl+Shift+B to build the project using the default task (this will trigger make).
 >  To clean the build, press Ctrl+Shift+B and select the "Clean Build" task.
 >  To run tests, press Ctrl+Shift+B and select the "Run Tests" task.

### 5. Debugging

For debugging, you can set up the launch.json configuration to run and step through the compiled executable. The default configuration in VSCode should automatically recognize the executable once it's built.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
Contributing

Feel free to fork this project, submit issues, or open pull requests if you have suggestions or improvements.