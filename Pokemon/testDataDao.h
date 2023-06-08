/**************************************************************
 * File : testDataDao.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: Header file defining the TestDataDao class, which is responsible for
 * data access operations related to testing data.
 *************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>

 // Forward declarations of classes.
class FileReader;
class TestDataParser;
class TestDataDaoPrivate;

class TestDataDao {
public:
    /**
     * Intent : Constructor for the TestDataDao class
     * Pre: A FileReader and a TestDataParser must exist before creating a TestDataDao instance.
     * Post: A new TestDataDao object is created with the given FileReader and TestDataParser.
     * \param kFileReader A shared_ptr to a FileReader instance.
     * \param kTestDataParser A shared_ptr to a TestDataParser instance.
     * \return A TestDataDao object.
     */
    TestDataDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser);

    /**
     * Intent : Destructor for the TestDataDao class
     * Pre: A TestDataDao object must exist.
     * Post: The TestDataDao object is destroyed and its resources are released.
     * \return None.
     */
    ~TestDataDao();

    /**
     * Intent : Retrieve test data from a given file path
     * Pre: A valid file path must be provided.
     * Post: Test data from the file at the provided path is retrieved and parsed.
     * \param kFilePath A string representing the file path to the test data.
     * \return A vector containing strings, representing the parsed test data.
     */
    std::vector<std::string> getData(const std::string& kFilePath);

private:
    // Private class data to encapsulate implementation details and improve information hiding.
    std::unique_ptr<TestDataDaoPrivate> mpPrivate;
};
