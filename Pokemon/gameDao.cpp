#include "gameDao.h"

#include "fileReader.h"
#include "gameDataParser.h"
#include "gameEntity.h"

class GameDaoPrivate {
public:
    GameDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser);

    std::shared_ptr<FileReader> mpFilerReader;  // File reader object to read the game data file
    std::shared_ptr<GameDataParser> mpGameDataParser;  // Game data parser object to parse the content of the file
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
    // Read the content of the file using the file reader
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);

    // Parse the content using the game data parser
    return mpPrivate->mpGameDataParser->parser(content);
}
