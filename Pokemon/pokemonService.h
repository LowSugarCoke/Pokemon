/**************************************************************
 * File : pokemonService.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: This file declares the PokemonService class.
 *              The class provides services for loading and manipulating
 *              data related to Pokemon game such as loading moves, Pokemon
 *              data, game data and testing data, getting Pokemons' names,
 *              swapping Pokemons, getting battle dialog, etc.
 **************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class MoveDao;
class PokemonDao;
class GameDao;
class TestDataDao;
class PokemonBo;
class PlayerMode;
class PokemonMode;
class PokemonServicePrivate;
class PokemonService {
public:

    /**
    * Intent : Constructor to initialize the PokemonService with DAOs and PlayerMode
    * Pre: DAOs and PlayerMode are correctly defined and instantiated
    * Post: PokemonService is correctly initialized
    * \param kMoveDao, kGameDao, kPokemonDao, kTestDataDao, kPlayerMode
    * \return Initialized instance of PokemonService
    */
    PokemonService(const std::shared_ptr<MoveDao>& kMoveDao, const std::shared_ptr<GameDao>& kGameDao,
        const std::shared_ptr<PokemonDao>& kPokemonDao, const std::shared_ptr< TestDataDao>& kTestDataDao, const std::shared_ptr<PlayerMode>& kPlayerMode);

    /**
     * Intent : Destructor for the PokemonService
     * Pre: PokemonService instance exists
     * Post: PokemonService instance is correctly destroyed
     * \return None
     */
    ~PokemonService();

    /**
     * Intent : Loads move, pokemon, and game data from provided file paths
     * Pre: File paths are valid and files exist
     * Post: Data is loaded into the PokemonService
     * \param kMoveFilePath, kPokemonFilePath, kGameFilePath
     * \return True if data loading was successful, false otherwise
     */
    bool loadData(const std::string& kMoveFilePath, const std::string& kPokemonFilePath, const std::string& kGameFilePath);

    /**
     * Intent : Loads test data from a file
     * Pre: The file path is valid and the file exists
     * Post: Test data is loaded into the PokemonService
     * \param kTestFilePath
     * \return True if the test data was loaded successfully, false otherwise
     */
    bool loadTestData(const std::string& kTestFilePath);

    /**
     * Intent : Retrieves the names of all Pokemons
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of Pokemon names
     */
    std::vector<std::string> getPokemonsName() const;

    /**
     * Intent : Retrieves the index of the current Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return The index of the current Pokemon
     */
    int getCurrentPokemonIndex() const;

    /**
     * Intent : Retrieves the names of opposing Pokemons
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of opposing Pokemon names
     */
    std::vector<std::string> getOppositingPokemonsName() const;

    /**
     * Intent : Retrieves the index of the current opposing Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return The index of the current opposing Pokemon
     */
    int getCurrentOppositingPokemonIndex() const;

    /**
     * Intent : Swaps the current opposing Pokemon
     * Pre: There are more than one opposing Pokemons available
     * Post: The current opposing Pokemon is swapped with the next in the list
     * \return True if the swap was successful, false otherwise
     */
    bool swapOppositingPokemon();

    /**
     * Intent : Retrieves the HP values of all Pokemons
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of pairs, where each pair contains the current HP and max HP of a Pokemon
     */
    std::vector<std::pair<int, int>> getPokemonsHp() const;

    /**
     * Intent : Retrieves the HP values of all opposing Pokemons
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of pairs, where each pair contains the current HP and max HP of an opposing Pokemon
     */
    std::vector<std::pair<int, int>> getOppositingPokemonsHp() const;

    /**
     * Intent : Retrieves the HP of the current opposing Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return The current HP of the opposing Pokemon
     */
    int getOppositingPokemonHp() const;

    /**
     * Intent : Retrieves the current additional effect of the current Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A set of strings representing the current additional effects
     */
    std::set<std::string> getCurrentPokemonAdditionalEffect() const;

    /**
     * Intent : Retrieves the current additional effect of the current opposing Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A set of strings representing the current additional effects of the opposing Pokemon
     */
    std::set<std::string> getOppositingPokemonAdditionalEffect() const;

    /**
     * Intent : Retrieves the current battle dialog
     * Pre: A battle has started
     * Post: None
     * \return The current battle dialog as a string
     */
    std::string getBattleDailog() const;

    /**
     * Intent : Changes the current Pokemon with another one from the list
     * Pre: There is more than one Pokemon available
     * Post: The current Pokemon has been swapped with the Pokemon at the provided index
     * \param kIndex
     */
    void swapPokemon(const int& kIndex);

    /**
     * Intent : Swaps the current Pokemon with another one from the list when the current one faints
     * Pre: There is more than one Pokemon available and the current Pokemon has fainted
     * Post: The current Pokemon has been swapped with the Pokemon at the provided index
     * \param kPokemonIndex
     * \return True if the swap was successful, false otherwise
     */
    bool faintingSwapPokemon(const int& kPokemonIndex);

    /**
     * Intent : Executes a battle round between the current Pokemon and an opposing Pokemon
     * Pre: Both Pokemons are ready for battle
     * Post: The battle round has been executed, modifying the states of the involved Pokemons
     * \param kMoveIndex, kOppositeIndex
     */
    void battle(const int& kMoveIndex, const int& kOppositeIndex = 0);

    /**
     * Intent : Retrieves the moves of the current Pokemon
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of strings representing the moves of the current Pokemon
     */
    std::vector<std::string> getCurrentPokemonMoves() const;

    /**
     * Intent : Uses a potion on a Pokemon
     * Pre: The Pokemon and the potion are available
     * Post: The potion has been used and the state of the Pokemon has been modified
     * \param kPokemonIndex, kPotionIndex
     */
    void usePotion(const int& kPokemonIndex, const int& kPotionIndex);

    /**
     * Intent : Retrieves the names of all available potions
     * Pre: Potions data has been loaded
     * Post: None
     * \return A vector of strings representing the names of all available potions
     */
    std::vector<std::string> getPotionsName() const;

    /**
     * Intent : Checks the faint status of all Pokemons
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of booleans representing the faint status of all Pokemons (true = fainted, false = not fainted)
     */
    std::vector<bool> getPokemonsFaintStatus() const;

    /**
     * Intent : Checks if the game has been won, lost, or is ongoing
     * Pre: A game is in progress
     * Post: None
     * \return An int representing the status of the game (0 = ongoing, 1 = won, 2 = lost)
     */
    int isWinOrLose() const;

    /**
     * Intent : Retrieves the types of the current Pokemon's moves
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of strings representing the types of the current Pokemon's moves
     */
    std::vector<std::string> getCurrentPokemonMoveTypes() const;

    /**
     * Intent : Retrieves the current power points of the current Pokemon's moves
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of integers representing the power points of the current Pokemon's moves
     */
    std::vector<int> getCurrentPokemonPowerPoints() const;

    /**
     * Intent : Retrieves the max power points of the current Pokemon's moves
     * Pre: Pokemon data has been loaded
     * Post: None
     * \return A vector of integers representing the power points of the current Pokemon's moves
     */
    std::vector<int> getCurrentPokemonMaxPowerPoints() const;

    /**
     * Intent : Checks if the current game mode is test mode
     * Pre: A game is in progress
     * Post: None
     * \return True if the game is in test mode, false otherwise
     */
    bool isTest() const;


private:
    std::unique_ptr<PokemonServicePrivate> mpPrivate;
};
