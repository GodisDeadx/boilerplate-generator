#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <string_view>

class Gen {
private:
    std::string m_fileName{"main"};
    std::string m_dirName{"."};
    std::string m_filePath;
    std::string m_cppFilePath;
    std::string m_headerFilePath;

public:
    Gen() {}

    void setFilePath() { // ensures file paths are correct
        m_cppFilePath = m_dirName + "/" + m_fileName + ".cpp";
        m_headerFilePath = m_dirName + "/main.h";
    }

    void setDirName(const std::string_view& dirName) {
        m_dirName = dirName;
    }

    void setFileName(const std::string_view& fileName) {
        m_fileName = fileName;
    }

    std::string getDirName() {
        return m_dirName;
    }

    std::string getFileName() {
        return m_fileName;
    }

    void createDirectory();

    void createFile(bool withHeader);

    void createHeader();

    void writeFile(const std::string& filePath, const std::string& content);

    void help(const std::string& name);
};

#endif /* GENERATOR_H */