/**************************************************************
 * File : pokemonDao.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file defining the PokemonDao class, which is responsible for
 *              data access operations related to Pokemon games.
 *************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>

 // Forward declarations of classes.
class FileReader;
class PokemonDataParser;
class PokemonEntity;
class PokemonDaoPrivate;

class PokemonDao {
public:
    /**
     * Intent : Constructor for the PokemonDao class
     * Pre: A FileReader and a PokemonDataParser must exist before creating a PokemonDao instance.
     * Post: A new PokemonDao object is created with the given FileReader and PokemonDataParser.
     * \param kFileReader A shared_ptr to a FileReader instance.
     * \param kPokemonDataParser A shared_ptr to a PokemonDataParser instance.
     * \return A PokemonDao object.
     */
    PokemonDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<PokemonDataParser>& kPokemonDataParser);

    /**
     * Intent : Destructor for the PokemonDao class
     * Pre: A PokemonDao object must exist.
     * Post: The PokemonDao object is destroyed and its resources are released.
     * \return None.
     */
    ~PokemonDao();

    /**
     * Intent : Retrieve Pokemon data from a given file path
     * Pre: A valid file path must be provided.
     * Post: Pokemon data from the file at the provided path is retrieved and parsed.
     * \param kFilePath A string representing the file path to the Pokemon data.
     * \return A vector containing PokemonEntity objects, representing the parsed Pokemon data.
     */
    std::vector<PokemonEntity> getData(const std::string& kFilePath);

private:
    // Private class data to encapsulate implementation details and improve information hiding.
    std::unique_ptr<PokemonDaoPrivate> mpPrivate;
};
