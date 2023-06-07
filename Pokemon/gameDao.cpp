#include "gameDao.h"

#include "fileReader.h"
#include "gameDataParser.h"
#include "gameEntity.h"

class GameDaoPrivate {
public:
    GameDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser);

    std::shared_ptr<FileReader> mpFilerReader;
    std::shared_ptr<GameDataParser> mpGameDataParser;
};

GameDaoPrivate::GameDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser)
    : mpFilerReader(kFileReader),
    mpGameDataParser(kGameDataParser)
{

}

GameDao::GameDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser)
    :mpPrivate(std::make_unique<GameDaoPrivate>(kFileReader, kGameDataParser))
{
}

GameDao::~GameDao() {}

std::pair<std::vector<GameEntity>, std::vector<GameEntity>>  GameDao::getData(const std::string& kFilePath) {
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);
    return mpPrivate->mpGameDataParser->parser(content);
}
