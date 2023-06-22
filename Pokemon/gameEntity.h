/**************************************************************
 * File : gameEntity.h
 * Author: Jack Lee
 * Create Date: 2023-06-06
 * Editor : Jack Lee
 * Update Date: 2023-06-06
 * Description: The GameEntity class defines the data and behavior of an entity in the game. This includes
 *              its name and the moves it can perform.
 *************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

 // Forward declaration of the private implementation class
class GameEntityPrivate;

class GameEntity {
public:

    /**
     * Intent : Default constructor for the GameEntity class
     * Pre: None
     * Post: A GameEntity object is initialized with default values
     */
    GameEntity();

    /**
     * Intent : Copy constructor for GameEntity
     * Pre: A valid GameEntity instance is provided
     * Post: A new instance of GameEntity is created as a copy of the provided instance
     * \param kGameEntity The GameEntity instance to be copied
     */
    GameEntity(const GameEntity& kGameEntity);


    /**
     * Intent : Overloaded constructor for the GameEntity class
     * Pre: kName is the desired name, kMovesVec contains the desired moves
     * Post: A GameEntity object is initialized with the given name and moves
     * \param kName
     * \param kMovesVec
     */
    GameEntity(const std::string& kName, const std::vector<std::string>& kMovesVec);


    /**
     * Intent : Destructs the GameEntity object and cleans up any resources associated with it.
     * Pre: None. The destructor is automatically invoked when the object goes out of scope or is explicitly deleted.
     * Post: The GameEntity object is destroyed and any associated resources are freed.
     */
    ~GameEntity();



    /**
     * Intent : Set the name of the GameEntity
     * Pre: kName is the desired name
     * Post: The name of the GameEntity is set to kName
     * \param kName
     */
    void setName(const std::string& kName);

    /**
     * Intent : Get the name of the GameEntity
     * Pre: None
     * Post: The name of the GameEntity is returned
     * \return
     */
    std::string getName() const;

    /**
     * Intent : Add a move to the GameEntity
     * Pre: kMove is the move to add
     * Post: The move kMove is added to the GameEntity's moves
     * \param kMove
     */
    void addMove(const std::string& kMove);

    /**
     * Intent : Get the moves of the GameEntity
     * Pre: None
     * Post: A vector containing the GameEntity's moves is returned
     * \return
     */
    std::vector<std::string> getMoves() const;

private:
    std::unique_ptr<GameEntityPrivate> mpPrivate;
};
