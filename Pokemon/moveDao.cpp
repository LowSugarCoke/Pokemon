#include "moveDao.h"

#include "fileReader.h"
#include "moveDataParser.h"
#include "moveEntity.h"

class MoveDaoPrivate {
public:
    MoveDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser);

    std::shared_ptr<FileReader> mpFilerReader;  // File reader object to read the move data file
    std::shared_ptr<MoveDataParser> mpMoveDataParser;  // Move data parser object to parse the content of the file
};

MoveDaoPrivate::MoveDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser)
    : mpFilerReader(kFileReader),
    mpMoveDataParser(kMoveDataParser)
{

}

MoveDao::MoveDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser)
    :mpPrivate(std::make_unique<MoveDaoPrivate>(kFileReader, kMoveDataParser))
{
}

MoveDao::~MoveDao() {}

std::vector<MoveEntity>  MoveDao::getData(const std::string& kFilePath) {
    // Read the content of the file using the file reader
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);

    // Parse the content using the move data parser
    return mpPrivate->mpMoveDataParser->parser(content);
}
