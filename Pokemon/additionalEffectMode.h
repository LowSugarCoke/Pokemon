/**************************************************************
 * File : additionalEffectMode.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: This file contains the declaration of the AdditionalEffectMode class, which represents a mode for handling additional effects in a game.
 *************************************************************/

#pragma once

#include <memory>

class MoveBo;
class PokemonBo;
class AdditionalEffectModePrivate;

class AdditionalEffectMode {
public:

    /**
     * Constructor.
     * Intent: Initializes an instance of the AdditionalEffectMode class.
     * Pre: None.
     * Post: An instance of the AdditionalEffectMode class is created.
     */
    AdditionalEffectMode();

    /**
     * Destructor.
     * Intent: Destroys an instance of the AdditionalEffectMode class.
     * Pre: None.
     * Post: The instance of the AdditionalEffectMode class is destroyed.
     */
    ~AdditionalEffectMode();

    /**
     * Checks if a Pokemon is unable to move.
     * Intent: Determines if the specified Pokemon is unable to move.
     * Pre: A valid shared pointer to a PokemonBo object is passed as an argument.
     * Post: Returns true if the Pokemon is unable to move, false otherwise.
     *
     * @param pPokemonBo A shared pointer to a PokemonBo object representing the Pokemon.
     * @return A boolean value indicating if the Pokemon is unable to move.
     */
    bool unableToMove(std::shared_ptr<PokemonBo> pPokemonBo) const;

    /**
     * Adds additional effects if a move has them.
     * Intent: Adds additional effects to the specified Pokemon based on the given move.
     * Pre: Valid shared pointers to a PokemonBo object and a MoveBo object are passed as arguments.
     * Post: The Pokemon's additional effects are updated based on the move.
     *
     * @param pPokemonBo A shared pointer to a PokemonBo object representing the Pokemon.
     * @param moveBo A MoveBo object representing the move.
     */
    void addIfMoveHasAdditionalEffect(std::shared_ptr<PokemonBo> pPokemonBo, MoveBo moveBo);

    /**
     * Applies additional damage after a battle.
     * Intent: Applies any additional damage to the specified Pokemon after a battle.
     * Pre: A valid shared pointer to a PokemonBo object is passed as an argument.
     * Post: The additional damage is applied to the Pokemon.
     *
     * @param pPokemonBo A shared pointer to a PokemonBo object representing the Pokemon.
     */
    void additionalDamageAfterBattle(std::shared_ptr<PokemonBo> pPokemonBo);

    /**
     * Sets a test mode.
     * Intent: Sets the AdditionalEffectMode to a test mode.
     * Pre: None.
     * Post: The AdditionalEffectMode is set to a test mode.
     */
    void setTest();

private:
    std::unique_ptr<AdditionalEffectModePrivate> mpPrivate;
};
