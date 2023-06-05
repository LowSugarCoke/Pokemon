#pragma once

#include <memory>
#include <vector>
#include <string>

class FileReader;
class MoveDataParser;
class MoveEntity;
class MoveDaoPrivate;
class MoveDao {
public:
    MoveDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser);
    ~MoveDao();
    std::vector<MoveEntity> getData(const std::string& kFilePath);
private:
    std::unique_ptr<MoveDaoPrivate> mpPrivate;
};
