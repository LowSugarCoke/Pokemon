#pragma once

#include <memory>
#include <vector>
#include <string>

class FileReader;
class PokemonDataParser;
class PokemonEntity;
class PokemonDaoPrivate;
class PokemonDao {
public:
    PokemonDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser);
    ~PokemonDao();
    std::vector<PokemonEntity> getData(const std::string& kFilePath);
private:
    std::unique_ptr<PokemonDaoPrivate> mpPrivate;
};
