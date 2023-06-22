/*******************************************************************
 * File: pokemonBo.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor: Jack Lee
 * Update Date: 2023-06-08
 * Description:
 *
 * This file defines the `MoveBo` struct and the `PokemonBo` class.
 *
 * The `MoveBo` struct represents a move that a Pokemon can perform.
 * It includes the move's name, type, damage type, statistical attributes,
 * and any additional effects.
 *
 * The `PokemonBo` class represents a Pokemon. It includes various methods
 * for managing a Pokemon's statistical attributes, the moves it can perform,
 * and its current state (such as HP and whether it is fainting).
 *
 * A Pokemon's statistical attributes are represented by the `PokemonStats` class,
 * and a move's statistical attributes are represented by the `MoveStats` class.
 * These classes are defined in separate files and are included in this file.
 *
 * This class utilizes a Pimpl Idiom ("Pointer to Implementation") to hide
 * private data, resulting in cleaner code and faster compilation times.
 *******************************************************************/


#pragma once

#include <memory>
#include <set>

#include "pokemonStats.h"
#include "type.h"
#include "moveStats.h"
#include "damageType.h"
#include "additionalEffectType.h"

struct MoveBo {
    std::string name;                   // Name of the Move
    TYPE type;                          // Type of the Move
    DAMAGE_TYPE damageType;              // Damage type of the Move
    MoveStats stats;                     // Statistical attributes of the Move
    ADDITIONAL_EFFECT_TYPE additionalEffectType;    // Additional effect of the Move
};

class MoveEntity;
class PokemonEntity;
class PokemonBoPrivate;

class PokemonBo {
public:

    /**
     * Intent: Constructs a PokemonBo object.
     * Pre: -
     * Post: A PokemonBo object is created.
     */
    PokemonBo();

    /**
     * Intent: Constructs a copy of the given PokemonBo object.
     * Pre: -
     * Post: A copy of the given PokemonBo object is created.
     * \param kPokemonBo: The PokemonBo object to be copied.
     */
    PokemonBo(const PokemonBo& kPokemonBo);

    /**
     * Intent: Destructs the PokemonBo object.
     * Pre: -
     * Post: The PokemonBo object is destructed.
     */
    ~PokemonBo();

    /**
     * Intent: Sets the elements of the PokemonBo object.
     * Pre: -
     * Post: The name, PokemonStats, and types of the Pokemon are set.
     * \param kName: The name of the Pokemon.
     * \param kPokemonStats: The statistical attributes of the Pokemon.
     * \param kType: The types of the Pokemon.
     */
    void setPokemonElements(const std::string& kName, const PokemonStats& kPokemonStats, const std::vector<TYPE>& kType);

    /**
     * Intent: Adds the elements of a move to the PokemonBo object.
     * Pre: -
     * Post: The name, MoveStats, type, damage type, and additional effect type of the move are added.
     * \param kName: The name of the move.
     * \param kMoveStats: The statistical attributes of the move.
     * \param kType: The type of the move.
     * \param kDamageType: The damage type of the move.
     * \param kAdditionalEffectType: The additional effect type of the move.
     */
    void addMoveElements(const std::string& kName, const MoveStats& kMoveStats, const TYPE& kType, const DAMAGE_TYPE& kDamageType, const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);

    /**
     * Intent: Adds the given amount to the current HP of the Pokemon.
     * Pre: -
     * Post: The given amount is added to the current HP of the Pokemon.
     * \param kHp: The amount of HP to be added.
     */
    void addHp(const int& kHp);

    /**
     * Intent: Subtracts the given amount from the current HP of the Pokemon.
     * Pre: -
     * Post: The given amount is subtracted from the current HP of the Pokemon.
     * \param kHp: The amount of HP to be subtracted.
     */
    void minusHp(const int& kHp);

    /**
     * Intent: Retrieves the PokemonStats of the PokemonBo object.
     * Pre: -
     * Post: The PokemonStats of the PokemonBo object is retrieved.
     * \return: The PokemonStats of the PokemonBo object.
     */
    PokemonStats getPokemonStats() const;

    /**
     * Intent: Finds and retrieves the MoveBo with the given move name.
     * Pre: -
     * Post: The MoveBo with the given move name is found and retrieved.
     * \param kMoveName: The name of the move to be found.
     * \return: The MoveBo with the given move name.
     */
    MoveBo findMoveBoByName(const std::string kMoveName);

    /**
     * Intent: Finds and retrieves the MoveBo with the given move index.
     * Pre: -
     * Post: The MoveBo with the given move index is found and retrieved.
     * \param kMonitorIndex: The index of the move to be found.
     * \return: The MoveBo with the given move index.
     */
    MoveBo findMoveBoByIndex(const int& kMonitorIndex);

    /**
     * Intent: Retrieves the vector of MoveBos.
     * Pre: -
     * Post: The vector of MoveBos is retrieved.
     * \return: The vector of MoveBos.
     */
    std::vector<MoveBo> getMoveBos() const;

    /**
     * Intent: Retrieves the types of the Pokemon.
     * Pre: -
     * Post: The types of the Pokemon are retrieved.
     * \return: The types of the Pokemon.
     */
    std::vector<TYPE> getPokemonTypes() const;

    /**
     * Intent: Checks if the Pokemon is fainting (HP <= 0).
     * Pre: -
     * Post: Whether the Pokemon is fainting is checked.
     * \return: True if the Pokemon is fainting, false otherwise.
     */
    bool isFainting();

    /**
     * Intent: Retrieves the maximum HP of the Pokemon.
     * Pre: -
     * Post: The maximum HP of the Pokemon is retrieved.
     * \return: The maximum HP of the Pokemon.
     */
    int getMaxHp() const;

    /**
     * Intent: Retrieves the current HP of the Pokemon.
     * Pre: -
     * Post: The current HP of the Pokemon is retrieved.
     * \return: The current HP of the Pokemon.
     */
    int getHp() const;

    /**
     * Intent: Sets the additional effect type of the Pokemon.
     * Pre: -
     * Post: The additional effect type of the Pokemon is set.
     * \param kAdditionalEffectType: The additional effect type to be set.
     */
    void setPokemonAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);

    /**
     * Intent: Retrieves the additional effect types of the Pokemon.
     * Pre: -
     * Post: The additional effect types of the Pokemon are retrieved.
     * \return: The additional effect types of the Pokemon.
     */
    std::set<ADDITIONAL_EFFECT_TYPE> getPokemonAdditionalEffectType() const;

    /**
     * Intent: Retrieves the name of the Pokemon.
     * Pre: -
     * Post: The name of the Pokemon is retrieved.
     * \return: The name of the Pokemon.
     */
    std::string getName() const;

    /**
     * Intent: Reduces the speed of the Pokemon by half.
     * Pre: -
     * Post: The speed of the Pokemon is reduced by half.
     */
    void reduceHalfSpeed();

    /**
     * Intent: Sets whether the Pokemon belongs to the player or the opponent.
     * Pre: -
     * Post: Whether the Pokemon belongs to the player or the opponent is set.
     * \param kMyPokemon: True if the Pokemon belongs to the player, false if it belongs to the opponent.
     */
    void checkToMyPokemon(const bool& kMyPokemon);

    /**
     * Intent: Checks if the Pokemon belongs to the player.
     * Pre: -
     * Post: Whether the Pokemon belongs to the player is checked.
     * \return: True if the Pokemon belongs to the player, false otherwise.
     */
    bool isMyPokemon() const;

    /**
     * Intent: Subtracts the power points (PP) of the move used by the Pokemon.
     * Pre: -
     * Post: The power points (PP) of the move used by the Pokemon are subtracted.
     * \param kMoveBo: The MoveBo representing the move used by the Pokemon.
     */
    void minusMovePowerPoint(const MoveBo& kMoveBo);

    /**
     * Intent: Retrieves the maximum power points (PP) of the moves of the Pokemon.
     * Pre: -
     * Post: The maximum power points (PP) of the moves of the Pokemon are retrieved.
     * \return: A vector containing the maximum power points (PP) of the moves.
     */
    std::vector<int> getMaxPowerPoint() const;

    /**
     * Intent: Finds the index of the move with the given move name.
     * Pre: -
     * Post: The index of the move with the given move name is found.
     * \param kMoveName: The name of the move to be found.
     * \return: The index of the move with the given move name.
     */
    int findMoveIndexByName(const std::string& kMoveName) const;

private:
    std::unique_ptr<PokemonBoPrivate> mpPrivate;
};
