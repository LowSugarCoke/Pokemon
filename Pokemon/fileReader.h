/**************************************************************
 * File : fileReader.h
 * Author: Jack Lee
 * Create Date: 2023-06-06
 * Editor : Jack Lee
 * Update Date: 2023-06-06
 * Description: This header file declares the FileReader class,
 *              which provides a method to read text files.
 *************************************************************/
#pragma once

#include <string>

class FileReader {
public:
    /**
     * Intent : Read the content of a text file at the given path into a string.
     *
     * Pre: kFilePath must be the path of a readable text file. If the file does not exist
     *      or cannot be read for any other reason, the function will throw a runtime_error.
     *
     * Post: Returns a string containing the content of the text file. If the file is empty,
     *       the returned string will be empty as well. The state of the file is unchanged,
     *       and it remains at the same location.
     *
     * \param kFilePath Path of the text file to read.
     * \return A string containing the content of the text file.
     */
    std::string readFile(const std::string& kFilePath) const;
};
