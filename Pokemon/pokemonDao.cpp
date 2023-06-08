#include "pokemonDao.h"

#include "fileReader.h"
#include "pokemonDataParser.h"
#include "pokemonEntity.h"

class PokemonDaoPrivate {
public:
    PokemonDaoPrivate(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser);

    std::shared_ptr<FileReader> mpFilerReader;  // File reader object to read the Pokémon data file
    std::shared_ptr<PokemonDataParser> mpPokemonDataParser;  // Pokémon data parser object to parse the content of the file
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
    // Read the content of the file using the file reader
    auto content = mpPrivate->mpFilerReader->readFile(kFilePath);

    // Parse the content using the Pokémon data parser
    return mpPrivate->mpPokemonDataParser->parser(content);
}
