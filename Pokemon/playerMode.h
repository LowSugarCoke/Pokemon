/**************************************************************
 * File : playerMode.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file for the PlayerMode class which defines the behavior and attributes
 *              of a player in a Pokemon-like game. Contains method definitions for actions
 *              like battling, swapping Pokemons, and using potions. Also provides access
 *              to information about player and opponent Pokemons.
 *************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>

class PokemonBo;
class PokemonMode;
class PlayerModePrivate;
class PlayerMode
{
public:

    /**
        * Intent : Constructs a PlayerMode instance.
        * Pre: pPokemonMode is a valid shared_ptr to a PokemonMode.
        * Post: A PlayerMode instance is created.
        * \param pPokemonMode Shared pointer to the PokemonMode.
        */
    PlayerMode(std::shared_ptr<PokemonMode> pPokemonMode);

    /**
     * Intent : Copy constructor for the PlayerMode class.
     * Pre: kPlayerMode is a valid PlayerMode instance.
     * Post: A new PlayerMode instance is created as a copy of the input instance.
     * \param kPlayerMode The PlayerMode instance to copy.
     */
    PlayerMode(const PlayerMode& kPlayerMode);

    /**
     * Intent : Destructor for the PlayerMode class.
     * Pre: Instance of PlayerMode exists.
     * Post: The PlayerMode instance is properly destroyed.
     */
    ~PlayerMode();

    /**
     * Intent : Sets the PokemonBo for the player.
     * Pre: pPokemonBoVec is a valid vector of shared_ptrs to PokemonBo.
     * Post: Player's PokemonBo is set.
     * \param pPokemonBoVec Vector of shared pointers to PokemonBo.
     */
    void setPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pPokemonBoVec);

    /**
     * Intent : Sets the opposing PokemonBo for the player.
     * Pre: pOppositingPokemonBoVec is a valid vector of shared_ptrs to PokemonBo.
     * Post: Player's opposing PokemonBo is set.
     * \param pOppositingPokemonBoVec Vector of shared pointers to opposing PokemonBo.
     */
    void setOppositingPokemonBo(std::vector<std::shared_ptr<PokemonBo>> pOppositingPokemonBoVec);

    /**
     * Intent : Swap the current Pokemon when it faints.
     * Pre: kPokemonIndex is a valid index into the Pokemon list.
     * Post: The current Pokemon is swapped with the Pokemon at the specified index.
     * \param kPokemonIndex The index of the Pokemon to swap.
     * \return Returns true if the swap was successful, false otherwise.
     */
    bool faintingSwapPokemon(const int& kPokemonIndex);

    /**
     * Intent : Swap the opposing Pokemon.
     * Pre: kPokemonIndex is a valid index into the opposing Pokemon list.
     * Post: The current opposing Pokemon is swapped with the Pokemon at the specified index.
     * \param kPokemonIndex The index of the Pokemon to swap.
     * \return Returns true if the swap was successful, false otherwise.
     */
    bool swapOppositingPokemon(const int& kPokemonIndex);

    /**
     * Intent : Swap the player's current Pokemon.
     * Pre: kPokemonIndex is a valid index into the Pokemon list.
     * Post: The current Pokemon is swapped with the Pokemon at the specified index.
     * \param kPokemonIndex The index of the Pokemon to swap.
     * \return Returns true if the swap was successful, false otherwise.
     */
    bool swapPokemon(const int& kPokemonIndex);

    /**
     * Intent : Initiates a battle between the current Pokemon and the opposing Pokemon.
     * Pre: kMoveIndex is a valid index into the move list and kOppositeIndex is a valid index into the opposing Pokemon list.
     * Post: A battle is initiated with the specified move and against the specified opposing Pokemon.
     * \param kMoveIndex The index of the move to use.
     * \param kOppositeIndex The index of the opposing Pokemon to battle.
     */
    void battle(const int& kMoveIndex, const int& kOppositeIndex = 0);


    /**
 * Intent : Retrieve names of all Pokemons owned by the player.
 * Pre: Player has Pokemons in their possession.
 * Post: Vector of Pokemon names is returned.
 * \return Vector of strings representing names of the player's Pokemons.
 */
    std::vector<std::string> getPokemonsName() const;

    /**
     * Intent : Retrieve HP status of all Pokemons owned by the player.
     * Pre: Player has Pokemons in their possession.
     * Post: Vector of pairs representing current and maximum HP of each Pokemon is returned.
     * \return Vector of pairs, each pair contains current HP (first) and max HP (second) of a Pokemon.
     */
    std::vector<std::pair<int, int>> getPokemonsHp() const;

    /**
     * Intent : Retrieve HP status of all Pokemons owned by the opponent.
     * Pre: Opponent has Pokemons in their possession.
     * Post: Vector of pairs representing current and maximum HP of each Pokemon is returned.
     * \return Vector of pairs, each pair contains current HP (first) and max HP (second) of a Pokemon.
     */
    std::vector<std::pair<int, int>> getOppositingPokemonsHp() const;

    /**
     * Intent : Retrieve additional effects on the current Pokemon.
     * Pre: Current Pokemon has additional effects (if any).
     * Post: Set of strings representing names of additional effects is returned.
     * \return Set of strings representing names of the additional effects on the current Pokemon.
     */
    std::set<std::string> getCurrentPokemonAdditionalEffect() const;

    /**
     * Intent : Retrieve additional effects on the current opposing Pokemon.
     * Pre: Current opposing Pokemon has additional effects (if any).
     * Post: Set of strings representing names of additional effects is returned.
     * \return Set of strings representing names of the additional effects on the current opposing Pokemon.
     */
    std::set<std::string> getOppositingPokemonAdditionalEffect() const;

    /**
     * Intent : Get the index of the current Pokemon.
     * Pre: Player has at least one Pokemon.
     * Post: Index of the current Pokemon is returned.
     * \return Index of the current Pokemon.
     */
    int getCurrentPokemonIndex() const;

    /**
     * Intent : Get the index of the current opposing Pokemon.
     * Pre: Opponent has at least one Pokemon.
     * Post: Index of the current opposing Pokemon is returned.
     * \return Index of the current opposing Pokemon.
     */
    int getOppositingPokemonIndex() const;

    /**
     * Intent : Retrieve names of all Pokemons owned by the opponent.
     * Pre: Opponent has Pokemons in their possession.
     * Post: Vector of Pokemon names is returned.
     * \return Vector of strings representing names of the opponent's Pokemons.
     */
    std::vector<std::string> getOppositingPokemonsName() const;

    /**
     * Intent : Retrieve available moves of the current Pokemon.
     * Pre: Current Pokemon has at least one move.
     * Post: Vector of strings representing names of the available moves is returned.
     * \return Vector of strings representing names of the available moves of the current Pokemon.
     */
    std::vector<std::string> getCurrentPokemonMoves() const;

    /**
     * Intent : Use a potion on a specific Pokemon.
     * Pre: kPokemonIndex is a valid index into the Pokemon list and kPotionIndex is a valid index into the potion list.
     * Post: The specified Pokemon's HP is restored using the potion at the specified index.
     * \param kPokemonIndex Index of the Pokemon to use the potion on.
     * \param kPotionIndex Index of the potion to use.
     */
    void usePotion(const int& kPokemonIndex, const int& kPotionIndex);

    /**
     * Intent : Retrieve names of all available potions.
     * Pre: There are potions available.
     * Post: Vector of strings representing names of the available potions is returned.
     * \return Vector of strings representing names of the available potions.
     */
    std::vector<std::string> getPotionsName() const;

    /**
     * Intent : Retrieve the faint status of all Pokemons owned by the player.
     * Pre: Player has Pokemons in their possession.
     * Post: Vector of booleans representing the faint status of each Pokemon is returned.
     * \return Vector of booleans representing the faint status of the player's Pokemons.
     */
    std::vector<bool> getPokemonsFaintStatus() const;

    /**
     * Intent : Determine if the player has won or lost the battle.
     * Pre: The battle has ended.
     * Post: Returns an integer indicating the battle result: 1 for win, -1 for loss, 0 for draw.
     * \return Integer indicating the battle result: 1 for win, -1 for loss, 0 for draw.
     */
    int isWinOrLose() const;

    /**
     * Intent : Retrieve the current opposing Pokemon's HP.
     * Pre: Opposing Pokemon is present.
     * Post: Current opposing Pokemon's HP is returned.
     * \return Current opposing Pokemon's HP.
     */
    int getOppositingPokemonHp() const;

    /**
     * Intent : Retrieve move types of the current Pokemon.
     * Pre: Current Pokemon has at least one move.
     * Post: Vector of strings representing move types is returned.
     * \return Vector of strings representing move types of the current Pokemon.
     */
    std::vector<std::string> getCurrentPokemonMoveTypes() const;

    /**
     * Intent : Retrieve power points (PP) of the current Pokemon's moves.
     * Pre: Current Pokemon has at least one move.
     * Post: Vector of integers representing current PP of each move is returned.
     * \return Vector of integers representing current PP of the current Pokemon's moves.
     */
    std::vector<int> getCurrentPokemonPowerPoints() const;

    /**
     * Intent : Retrieve maximum power points (PP) of the current Pokemon's moves.
     * Pre: Current Pokemon has at least one move.
     * Post: Vector of integers representing maximum PP of each move is returned.
     * \return Vector of integers representing maximum PP of the current Pokemon's moves.
     */
    std::vector<int> getCurrentPokemonMaxPowerPoints() const;

    /**
     * Intent : Set the player in test mode.
     * Pre: -
     * Post: The player is set in test mode.
     */
    void setTest();

    /**
     * Intent : Run a test using the provided test data.
     * Pre: Player is in test mode and test data is valid.
     * Post: The test is executed using the provided test data.
     * \param kTestData Vector of strings representing the test data.
     */
    void runTest(const std::vector<std::string>& kTestData);

private:
    std::unique_ptr<PlayerModePrivate> mpPrivate;
};
