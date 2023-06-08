#include "gameEntity.h"

class GameEntityPrivate {
public:
    std::string mName;
    std::vector<std::string> mMovesVec;
};

// Default constructor
GameEntity::GameEntity()
    : mpPrivate(std::make_unique<GameEntityPrivate>())
{
    // Initialize the name to an empty string
    mpPrivate->mName = "";
}

// Parameterized constructor
GameEntity::GameEntity(const std::string& kName, const std::vector<std::string>& kMovesVec)
    : mpPrivate(std::make_unique<GameEntityPrivate>())
{
    // Set the name and moves vector using the provided parameters
    setName(kName);
    mpPrivate->mMovesVec = kMovesVec;
}

// Copy constructor
GameEntity::GameEntity(const GameEntity& kGameEntity)
    : mpPrivate(std::make_unique<GameEntityPrivate>(*kGameEntity.mpPrivate)) {
    // Perform a deep copy of the private member using the unique pointer
}

// Destructor
GameEntity::~GameEntity() {
    // Destructor is automatically generated for the unique pointer
}

// Set the name of the game entity
void GameEntity::setName(const std::string& kName) {
    mpPrivate->mName = kName;
}

// Get the name of the game entity
std::string GameEntity::getName() const {
    return mpPrivate->mName;
}

// Add a move to the game entity's moves vector
void GameEntity::addMove(const std::string& kMove) {
    mpPrivate->mMovesVec.push_back(kMove);
}

// Get the moves vector of the game entity
std::vector<std::string> GameEntity::getMoves() const {
    return mpPrivate->mMovesVec;
}
