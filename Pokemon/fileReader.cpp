#include "fileReader.h"

#include <fstream>
#include <sstream>

std::string FileReader::readFile(const std::string& kFilePath) const {
    std::ifstream file(kFilePath);

    if (!file) {
        throw std::runtime_error("Could not open file: " + kFilePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}
