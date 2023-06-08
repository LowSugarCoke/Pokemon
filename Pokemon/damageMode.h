/**************************************************************
 * File : damageMode.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This header file defines the class DamageMode,
 *              which is used to model and calculate damage
 *              in a Pokemon-like battle system.
 *************************************************************/
#pragma once

#include <memory>
#include <string>
#include "pokemonBo.h"

class DamageModePrivate;
class DamageMode {
public:
    /**
     * Intent : Default constructor for DamageMode.
     * Pre: None.
     * Post: An instance of DamageMode is created.
     */
    DamageMode();

    /**
     * Intent : Copy constructor for DamageMode.
     * Pre: The input must be a DamageMode instance.
     * Post: A new instance of DamageMode is created, being a copy of the input instance.
     * \param kDamageMode A const reference to the DamageMode instance to copy.
     */
    DamageMode(const DamageMode& kDamageMode);

    /**
     * Intent : Destructor for DamageMode.
     * Pre: None.
     * Post: The DamageMode instance is properly destroyed.
     */
    ~DamageMode();

    /**
     * Intent : Function to determine if an attack misses.
     * Pre: The attacking and defending Pokemon must be valid instances. MoveBo instance also needs to be valid.
     * Post: Returns a boolean indicating whether the attack misses or not.
     * \param pMyPokemonBo A shared pointer to the attacking Pokemon.
     * \param pTargetPokemonBo A shared pointer to the defending Pokemon.
     * \param kMoveBo A const reference to the move being used.
     * \return boolean indicating whether the attack misses.
     */
    bool isMissing(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo);

    /**
     * Intent : Function to calculate the damage inflicted by an attack.
     * Pre: The attacking and defending Pokemon must be valid instances. MoveBo instance also needs to be valid.
     * Post: Returns the calculated damage.
     * \param pMyPokemonBo A shared pointer to the attacking Pokemon.
     * \param pTargetPokemonBo A shared pointer to the defending Pokemon.
     * \param kMoveBo A const reference to the move being used.
     * \return Calculated damage as an integer.
     */
    int damageCalculate(std::shared_ptr<PokemonBo> pMyPokemonBo, std::shared_ptr<PokemonBo> pTargetPokemonBo, const MoveBo& kMoveBo);

    /**
     * Intent : A function for test setting.
     * Pre: None.
     * Post: Test settings are applied.
     */
    void setTest();

private:
    /**
     * Intent: A unique pointer to a DamageModePrivate instance.
     * This instance is used for keeping the implementation details of DamageMode hidden (PIMPL idiom).
     */
    std::unique_ptr<DamageModePrivate> mpPrivate;
};
