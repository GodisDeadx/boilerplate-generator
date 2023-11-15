# Project Name

**C++ Project Generator**

## Overview

This project is a simple C++ project generator tool that facilitates the creation of project directories, files, and provides various options for customization.

## Features

- **Create Directory:** Checks for the existence of a directory; if not found, creates one.
- **Create File:** Generates a C++ file with customizable content.
- **Create Header:** Generates a header file.
- **Command-Line Interface:** Supports a range of command-line options for flexible project setup.

## Flags:

- `-h`, `--help`: Display the help message.
- `-nh`, `--no-header`: Create a C++ project without the header file.
- `-n <DIRNAME>`: Create a project with the specified name.
- `-fn <FILENAME>`: Specify a name for the file.
- `-f <FILENAME>`: Create a C++ file in the current directory.

## Building and Running

1. **Clone the Repository:**
```bash
   git clone https://github.com/GodisDeadx/boilerplate-generator.git
   cd boilerplate-gen
```
2. **Create a Build Directory:**
```bash
    mkdir build
    cd build
```
3. **Run CMake & Make:**
```bash
    cmake ..
    make
```

4. **Run The Executable:**
```bash
    ./gen <FLAGS> -n <DIRNAME>
```
- Optional
```bash
   sudo mv gen /bin/gen
``` 
