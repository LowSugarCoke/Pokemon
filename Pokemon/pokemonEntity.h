/**************************************************************
 * File : pokemonEntity.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-06
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-06
 * Description: The PokemonEntity class defines the data and behavior of a Pokemon entity in the game. This includes
 * its name, types, and stats.
 *************************************************************/
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "type.h"
#include "pokemonStats.h"

 // Forward declaration of the private implementation class
class PokemonEntityPrivate;

class PokemonEntity {
public:

    /**
     * Intent : Default constructor for the PokemonEntity class
     * Pre: None
     * Post: A PokemonEntity object is initialized with default values
     */
    PokemonEntity();

    /**
     * Intent : Overloaded constructor for the PokemonEntity class
     * Pre: kName is the desired name, kTypeVec contains the desired types, kStats contains the desired stats
     * Post: A PokemonEntity object is initialized with the given name, types, and stats
     * \param kName
     * \param kTypeVec
     * \param kStats
     */
    PokemonEntity(const std::string& kName, const std::vector<TYPE>& kTypeVec, const PokemonStats& kStats);

    /**
     * Intent : Copy constructor for PokemonEntity
     * Pre: A valid PokemonEntity instance is provided
     * Post: A new instance of PokemonEntity is created as a copy of the provided instance
     * \param kPokemonEntity The PokemonEntity instance to be copied
     */
    PokemonEntity(const PokemonEntity& kPokemonEntity);

    /**
     * Intent : Destructs the PokemonEntity object and cleans up any resources associated with it.
     * Pre: None. The destructor is automatically invoked when the object goes out of scope or is explicitly deleted.
     * Post: The PokemonEntity object is destroyed and any associated resources are freed.
     */
    ~PokemonEntity();

    /**
     * Intent : Set the name of the Pokemon
     * Pre: kName is the desired name
     * Post: The name of the Pokemon is set to kName
     * \param kName
     */
    void setName(const std::string& kName);

    /**
     * Intent : Get the name of the Pokemon
     * Pre: None
     * Post: The name of the Pokemon is returned
     * \return
     */
    std::string getName() const;

    /**
     * Intent : Add a type to the Pokemon
     * Pre: kType is the type to add
     * Post: The type kType is added to the Pokemon's types
     * \param kType
     */
    void addType(const TYPE& kType);

    /**
     * Intent : Get the types of the Pokemon
     * Pre: None
     * Post: A vector containing the Pokemon's types is returned
     * \return
     */
    std::vector<TYPE> getTypes() const;

    /**
     * Intent : Set the stats of the Pokemon
     * Pre: kStats contains the desired stats
     * Post: The stats of the Pokemon are set to kStats
     * \param kStats
     */
    void setStats(const PokemonStats& kStats);

    /**
     * Intent : Get the stats of the Pokemon
     * Pre: None
     * Post: A PokemonStats object containing the Pokemon's stats is returned
     * \return
     */
    PokemonStats getStats() const;

    PokemonEntity& operator=(const PokemonEntity& kPokemonEntity);


private:
    std::unique_ptr<PokemonEntityPrivate> mpPrivate;

};
