#include "fileReader.h"

#include <fstream>
#include <sstream>

std::string FileReader::readFile(const std::string& kFilePath) const {
    std::ifstream file(kFilePath); // Open the file for reading

    if (!file) {
        throw std::runtime_error("Could not open file: " + kFilePath); // Throw an exception if the file cannot be opened
    }

    std::stringstream buffer; // Create a string stream to store the file content
    buffer << file.rdbuf(); // Read the entire file content into the string stream

    file.close(); // Close the file

    return buffer.str(); // Return the content of the file as a string
}
