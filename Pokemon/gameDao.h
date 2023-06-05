#pragma once

#include <memory>
#include <vector>
#include <string>

class FileReader;
class GameDataParser;
class GameEntity;
class GameDaoPrivate;
class GameDao {
public:
    GameDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser);
    ~GameDao();
    std::vector<GameEntity> getData(const std::string& kFilePath);
private:
    std::unique_ptr<GameDaoPrivate> mpPrivate;
};
