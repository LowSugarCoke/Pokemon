#include "moveDao.h"

#include "fileReader.h"
#include "moveDataParser.h"
#include "moveEntity.h"

class MoveDaoPrivate {
public:
    MoveDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser);

    std::shared_ptr<FileReader> mpFilerReader;
    std::shared_ptr<MoveDataParser> mpMoveDataParser;
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
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);
    return mpPrivate->mpMoveDataParser->parser(content);
}
