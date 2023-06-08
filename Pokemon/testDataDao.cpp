#include "testDataDao.h"

#include "fileReader.h"
#include "testDataParser.h"

class TestDataDaoPrivate {
public:
    TestDataDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser);

    std::shared_ptr<FileReader> mpFilerReader;  // File reader object to read the test data file
    std::shared_ptr<TestDataParser> mpTestDataParser;  // Test data parser object to parse the content of the file
};

TestDataDaoPrivate::TestDataDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser)
    : mpFilerReader(kFileReader),
    mpTestDataParser(kTestDataParser)
{

}

TestDataDao::TestDataDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser)
    :mpPrivate(std::make_unique<TestDataDaoPrivate>(kFileReader, kTestDataParser))
{
}

TestDataDao::~TestDataDao() {}

std::vector<std::string>  TestDataDao::getData(const std::string& kFilePath) {
    // Read the content of the file using the file reader
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);

    // Parse the content using the test data parser
    return mpPrivate->mpTestDataParser->parser(content);
}
