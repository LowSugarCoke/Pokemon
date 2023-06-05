#include "pokemonDao.h"

#include "fileReader.h"
#include "pokemonDataParser.h"
#include "pokemonEntity.h"

class PokemonDaoPrivate {
public:
    PokemonDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser);

    std::shared_ptr<FileReader> mpFilerReader;
    std::shared_ptr<PokemonDataParser> mpPokemonDataParser;
};

PokemonDaoPrivate::PokemonDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser)
    : mpFilerReader(kFileReader),
    mpPokemonDataParser(kPokemonDataParser)
{

}

PokemonDao::PokemonDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser)
    :mpPrivate(std::make_unique<PokemonDaoPrivate>(kFileReader, kPokemonDataParser))
{
}

PokemonDao::~PokemonDao() {}

std::vector<PokemonEntity>  PokemonDao::getData(const std::string& kFilePath) {
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);
    return mpPrivate->mpPokemonDataParser->parser(content);
}
