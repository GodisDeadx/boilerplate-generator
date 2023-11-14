#include <iostream>
#include <stdio.h>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "../include/generator.h"
#include "../include/sleep.h"

void Gen::createCMake() {
    std::string file = m_dirName + "/CMakeLists.txt";
    std::string content = "cmake_minimum_required(VERSION 3.10)\nproject(" + getDirName() + " CXX)\n\n# Add source files to the project\nadd_executable(" + getFileName() + " ./src/main.cpp)";
    writeFile(file, content);
    std::cout << "CMakeLists.txt Created!\n";
}

void Gen::createStructure(bool withHeader) {
    std::string dirname = m_dirName;
    std::string src_dirname = m_dirName + "/src";
    std::string inc_dirname = m_dirName + "/include";
    // Create src/ directory
    setDirName(src_dirname);
    createDirectory();
    // Create include/ directory
    if (withHeader) {
        setDirName(inc_dirname);
        createDirectory();
    }
}

void Gen::createDirectory() {
    if (!std::filesystem::exists(m_dirName)) {
        if (std::filesystem::create_directory(m_dirName)) {
            sleep::milliseconds(100);
        } else {
            std::cout << m_dirName << " Could Not Be Created!\n";
            exit(1);
        }
    } else {
        std::cout << m_dirName << " Already Exists!\n";
        exit(1);
    }
}

void Gen::createFile(bool withHeader) {
    std::string fileContent = "int main(){\n\nreturn 0;\n}";

    if (withHeader) {
        fileContent = "#include <iostream>\n#include \"main.h\"\n\n" + fileContent;
    } else {
        fileContent = "#include <iostream>\n\n" + fileContent;
    }

    writeFile(m_cppFilePath, fileContent);
    std::cout << m_cppFilePath << " Created!\n";
    if(withHeader){
        createHeader();
    }
}

void Gen::createHeader() {
    std::string fileContent = "#pragma once\n\n";
    writeFile(m_headerFilePath, fileContent);
    std::cout << m_headerFilePath << " Created!\n";
}

void Gen::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    file << content;
    file.close();
}

void Gen::help(const std::string& name) {
    std::cout << "Usage: " << name << " <FLAGS> -dir <DIRNAME>\n"
              << "Flags:\n"
              << "-h, --help\t\tDisplay This Message\n"
              << "-nh, --no-header\tCreate a C++ Project Without The Header File.\n"
              << "-dir <DIRNAME>\t\tCreate a Directory With The Specified Name\n"
              << "-fn <FILENAME>\t\tSpecify a Name For The File\n"
              << "-f <FILENAME>\t\tCreate a C++ File In Current Directory\n";
    exit(0);
}

enum class Mode {

    Invalid,
    Cpp,
    CppNoHeader,

};

const std::unordered_map<std::string, Mode> modeMap {

    {"-nh", Mode::CppNoHeader},
    {"--no-header", Mode::CppNoHeader},

}; 

int main(int argc, char** argv) {

    std::string fileName{ "main" }, dirName{"error"};
    Mode mode = Mode::Cpp;
    Gen gen;

    if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        gen.help(argv[0]);
    }

    for (int j = 1; j < argc; ++j) {
        std::string arg = argv[j];
        if (arg == "-dir") {
            gen.setDirName(argv[j + 1]);
            dirName = argv[j + 1];
        } else if (arg == "-fn") {
            gen.setFileName(argv[j + 1]);
        } else if (arg == "-f"){
            gen.setFileName(argv[j + 1]);
            gen.setFilePath();
            gen.createFile(false);
            return 0;
        } else if (modeMap.count(arg)) {
            mode = modeMap.at(arg);
        }
    }

    gen.setFilePath(); /* set the file paths of the cpp and h file  */

    if (gen.getDirName() != dirName) {
        std::cout << "Failed to get the directory name.\n";
        return 0;
    }

    switch (mode) {
        case Mode::CppNoHeader:
            std::cout << "Creating C++ Project!\n";
            std::cout << "Header File Creation Disabled!\n\n";
            gen.createDirectory();
            gen.createCMake();
            gen.createStructure(false);
            gen.createFile(false);
            break;
        case Mode::Cpp:
            std::cout << "Creating " << gen.getFileName() << " Project!\n\n";
            gen.createDirectory();
            gen.createCMake();
            gen.createStructure(true);
            gen.createFile(true);
            break;
        default:
            std::cout << "Invalid Argument!\n";
            return 0;
    }

    return 0;
}