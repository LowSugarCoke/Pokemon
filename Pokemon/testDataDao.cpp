#include "testDataDao.h"

#include "fileReader.h"
#include "testDataParser.h"

class TestDataDaoPrivate {
public:
    TestDataDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<TestDataParser>& kTestDataParser);

    std::shared_ptr<FileReader> mpFilerReader;
    std::shared_ptr<TestDataParser> mpTestDataParser;
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
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);
    return mpPrivate->mpTestDataParser->parser(content);
}
