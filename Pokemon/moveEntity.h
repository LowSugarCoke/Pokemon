/**************************************************************
 * File : moveEntity.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-06
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-06
 * Description: This file defines the MoveEntity class and MoveStats struct
 * used in a game, such as Pokemon. Each move has a name, type, damage type,
 * move stats (power, accuracy, powerPoint), and additional effects.
 *************************************************************/
#pragma once

#include <memory>
#include <string>

#include "type.h"
#include "damageType.h"
#include "additionalEffectType.h"
#include "moveStats.h"



class MoveEntityPrivate;  // Forward declaration of MoveEntityPrivate class
class MoveEntity {
public:

    /**
     * Intent : Default constructor for MoveEntity
     * Pre: None
     * Post: An instance of MoveEntity is created
     */
    MoveEntity();

    /**
     * Intent : Overloaded constructor for MoveEntity
     * Pre: Valid inputs for name, type, damage type, move stats and additional effects are provided
     * Post: An instance of MoveEntity is created with specified attributes
     * \param kName Name of the Move
     * \param kType Type of the Move
     * \param kDamageType Damage type of the Move
     * \param kMoveStats Statistical attributes of the Move
     * \param kAdditionalEffectType Additional effect of the Move
     */
    MoveEntity(const std::string& kName, const TYPE& kType, const DAMAGE_TYPE& kDamageType, const MoveStats& kMoveStats, const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);


    /**
     * Intent : Copy constructor for MoveEntity
     * Pre: A valid MoveEntity instance is provided
     * Post: A new instance of MoveEntity is created as a copy of the provided instance
     * \param kMoveEntity The MoveEntity instance to be copied
     */
    MoveEntity(const MoveEntity& kMoveEntity);

    /**
     * Intent : Destructs the MoveEntity object and cleans up any resources associated with it.
     * Pre: None. The destructor is automatically invoked when the object goes out of scope or is explicitly deleted.
     * Post: The MoveEntity object is destroyed and any associated resources are freed.
     */
    ~MoveEntity();


    /**
     * Intent : Sets the name of the Move
     * Pre: A valid string for name is provided
     * Post: The name of the Move is updated
     * \param kName The name to be set for the Move
     */
    void setName(const std::string& kName);

    /**
     * Intent : Retrieves the name of the Move
     * Pre: None
     * Post: The name of the Move is returned
     * \return The name of the Move
     */
    std::string getName() const;

    /**
     * Intent : Sets the type of the Move
     * Pre: A valid TYPE is provided
     * Post: The type of the Move is updated
     * \param kType The type to be set for the Move
     */
    void setType(const TYPE& kType);

    /**
     * Intent : Retrieves the type of the Move
     * Pre: None
     * Post: The type of the Move is returned
     * \return The type of the Move
     */
    TYPE getType() const;

    /**
     * Intent : Sets the damage type of the Move
     * Pre: A valid DAMAGE_TYPE is provided
     * Post: The damage type of the Move is updated
     * \param kDamageType The damage type to be set for the Move
     */
    void setDamageType(const DAMAGE_TYPE& kDamageType);

    /**
     * Intent : Retrieves the damage type of the Move
     * Pre: None
     * Post: The damage type of the Move is returned
     * \return The damage type of the Move
     */
    DAMAGE_TYPE getDamageType() const;

    /**
     * Intent : Sets the statistical attributes of the Move
     * Pre: A valid MoveStats object is provided
     * Post: The statistical attributes of the Move are updated
     * \param kMoveStats The statistical attributes to be set for the Move
     */
    void setMoveStats(const MoveStats& kMoveStats);

    /**
     * Intent : Retrieves the statistical attributes of the Move
     * Pre: None
     * Post: The statistical attributes of the Move are returned
     * \return The statistical attributes of the Move
     */
    MoveStats getMoveStats() const;

    /**
     * Intent : Sets the additional effect of the Move
     * Pre: A valid ADDITIONAL_EFFECT_TYPE is provided
     * Post: The additional effect of the Move is updated
     * \param kAdditionalEffectType The additional effect to be set for the Move
     */
    void setAdditionalEffectType(const ADDITIONAL_EFFECT_TYPE& kAdditionalEffectType);

    /**
     * Intent : Retrieves the additional effect of the Move
     * Pre: None
     * Post: The additional effect of the Move is returned
     * \return The additional effect of the Move
     */
    ADDITIONAL_EFFECT_TYPE getAdditionalEffectType() const;

private:
    std::unique_ptr<MoveEntityPrivate> mpPrivate;  // Pointer to the private implementation of the MoveEntity class
};
