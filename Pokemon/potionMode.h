/**************************************************************
 * File : potionMode.h
 * Author: Jack Lee
 * Create Date: 2023-06-09
 * Editor : Jack Lee
 * Update Date: 2023-06-09
 * Description: Header file for the PotionMode class which represents the mode of a potion in the game.
 *              It provides functionality to add HP to a Pokemon using potions.
 *************************************************************/
#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>

class PokemonBo;
class PotionModePrivate;
class PotionMode {
public:

    /**
     * Intent : Constructs a PotionMode instance.
     * Pre: -
     * Post: A PotionMode instance is created.
     */
    PotionMode();

    /**
     * Intent : Destructor for the PotionMode class.
     * Pre: Instance of PotionMode exists.
     * Post: The PotionMode instance is properly destroyed.
     */
    ~PotionMode();

    /**
     * Intent : Copy constructor for the PotionMode class.
     * Pre: kPotionMode is a valid PotionMode instance.
     * Post: A new PotionMode instance is created as a copy of the input instance.
     * \param kPotionMode The PotionMode instance to copy.
     */
    PotionMode(const PotionMode& kPotionMode);

    /**
     * Intent : Retrieve names of all available potions.
     * Pre: There are potions available.
     * Post: Vector of strings representing names of the available potions is returned.
     * \return Vector of strings representing names of the available potions.
     */
    std::vector<std::string> getPotionsName() const;

    /**
     * Intent : Add HP to a specific Pokemon using a potion.
     * Pre: pPokemonBo is a valid shared_ptr to a PokemonBo and kPotionIndex is a valid index into the potion list.
     * Post: The specified Pokemon's HP is increased using the potion at the specified index.
     * \param pPokemonBo Shared pointer to the PokemonBo to add HP to.
     * \param kPotionIndex Index of the potion to use.
     */
    void addHp(std::shared_ptr<PokemonBo> pPokemonBo, const int& kPotionIndex);

private:
    std::unique_ptr<PotionModePrivate> mpPrivate;
};
