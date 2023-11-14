#include "generator.h"
#include <iostream>
#include <filesystem>
#include <fstream>

void Gen::createDirectory() {
    if (!std::filesystem::exists(m_dirName)) {
        if (std::filesystem::create_directory(m_dirName)) {
            std::cout << m_dirName << " Created!\n";
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
        createHeader();
    } else {
        fileContent = "#include <iostream>\n\n" + fileContent;
    }

    writeFile(m_cppFilePath, fileContent);
    std::cout << m_cppFilePath << " Created!\n";
}

void Gen::createHeader() {
    std::string fileContent = "#pragma once\n\n";
    writeFile(m_headerFilePath, fileContent);
}

void Gen::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    file << content;
    file.close();
}

void help([[optional]] const std::string& name) {
    std::cout << "Usage: " << name << " <FLAGS> -dir <DIRNAME>\n"
              << "Flags:\n"
              << "-h, --help\t\tDisplay This Message\n"
              << "-cpp\t\t\tCreate a C++ Project\n"
              << "-nh, --no-header\tCreate a C++ Project Without The Header File. Must Be Used With -cpp\n"
              << "-dir <DIRNAME>\t\tCreate a Directory With The Specified Name\n"
              << "-fn <FILENAME>\t\tSpecify a Name For The File\n"
              << "-f <FILENAME>\t\tCreate a C++ File In Current Directory\n";
    exit(0);
}