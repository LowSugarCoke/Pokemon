/**************************************************************
 * File : pokemonMode.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file for the PokemonMode class which represents the mode of a Pokemon in the game.
 *              It manages the behavior and attributes of a Pokemon, including damage calculation,
 *              additional effects, and potion usage.
 *************************************************************/
#pragma once

#include <memory>
#include <string>
#include <vector>

class PokemonBo;
class AdditionalEffectMode;
class DamageMode;
class PotionMode;
class PokemonModePrivate;
class PokemonMode {
public:
    /**
     * Intent : Constructs a PokemonMode instance.
     * Pre: pDamageMode, pAdditionalEffectMode, and pPotionMode are valid shared_ptrs.
     * Post: A PokemonMode instance is created.
     * \param pDamageMode Shared pointer to the DamageMode.
     * \param pAdditionalEffectMode Shared pointer to the AdditionalEffectMode.
     * \param pPotionMode Shared pointer to the PotionMode.
     */
    PokemonMode(std::shared_ptr<DamageMode> pDamageMode, std::shared_ptr<AdditionalEffectMode> pAdditionalEffectMode, std::shared_ptr<PotionMode> pPotionMode);

    /**
     * Intent : Copy constructor for the PokemonMode class.
     * Pre: kPokemonMode is a valid PokemonMode instance.
     * Post: A new PokemonMode instance is created as a copy of the input instance.
     * \param kPokemonMode The PokemonMode instance to copy.
     */
    PokemonMode(const PokemonMode& kPokemonMode);

    /**
     * Intent : Destructor for the PokemonMode class.
     * Pre: Instance of PokemonMode exists.
     * Post: The PokemonMode instance is properly destroyed.
     */
    ~PokemonMode();

    /**
     * Intent : Sets the player's Pokemon.
     * Pre: pMyPokemon is a valid shared_ptr to a PokemonBo.
     * Post: Player's Pokemon is set.
     * \param pMyPokemon Shared pointer to the player's Pokemon.
     */
    void setMyPokemon(std::shared_ptr<PokemonBo> pMyPokemon);

    /**
     * Intent : Sets the opposing Pokemon.
     * Pre: pOppositingPokemon is a valid shared_ptr to a PokemonBo.
     * Post: Opposing Pokemon is set.
     * \param pOppositingPokemon Shared pointer to the opposing Pokemon.
     */
    void setOppositingPokemon(std::shared_ptr<PokemonBo> pOppositingPokemon);

    /**
     * Intent : Proceed to the next round of battle with attack.
     * Pre: kMoveIndex is a valid index into the move list and kOppositeIndex is a valid index into the opposing Pokemon list.
     * Post: The next round of battle is executed with the specified move and against the specified opposing Pokemon.
     * \param kMoveIndex The index of the move to use.
     * \param kOppositeIndex The index of the opposing Pokemon to battle.
     */
    void nextRound(const int& kMoveIndex, const int& kOppositeIndex = 0);

    /**
     * Intent : Proceed to the next round of battle without attack.
     * Pre: kOppositeIndex is a valid index into the opposing Pokemon list.
     * Post: The next round of battle is executed without any attack against the specified opposing Pokemon.
     * \param kOppositeIndex The index of the opposing Pokemon to battle.
     */
    void nextRoundWithoutAttack(const int& kOppositeIndex = 0);

    /**
     * Intent : Use a potion on a specific Pokemon.
     * Pre: pPokemonBo is a valid shared_ptr to a PokemonBo and kPotionIndex is a valid index into the potion list.
     * Post: The specified Pokemon's HP is restored using the potion at the specified index.
     * \param pPokemonBo Shared pointer to the PokemonBo to use the potion on.
     * \param kPotionIndex Index of the potion to use.
     */
    void usePotion(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex);

    /**
     * Intent : Retrieve names of all available potions.
     * Pre: There are potions available.
     * Post: Vector of strings representing names of the available potions is returned.
     * \return Vector of strings representing names of the available potions.
     */
    std::vector<std::string> getPotionsName() const;

    /**
     * Intent : Set the PokemonMode in test mode.
     * Pre: -
     * Post: The PokemonMode is set in test mode.
     */
    void setTest();

    /**
     * Intent : Set the last opposing Pokemon.
     * Pre: -
     * Post: The last opposing Pokemon is set for testing purposes.
     */
    void setLastOppositePokemon();

private:
    std::unique_ptr<PokemonModePrivate> mpPrivate;
};
