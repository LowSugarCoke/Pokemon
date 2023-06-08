#pragma once

#include <memory>
#include <vector>
#include <string>

class FileReader;
class TestDataParser;
class TestDataDaoPrivate;
class TestDataDao {
public:
    TestDataDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser);
    ~TestDataDao();
    std::vector<std::string> getData(const std::string& kFilePath);
private:
    std::unique_ptr<TestDataDaoPrivate> mpPrivate;
};
