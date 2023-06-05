#include "gameEntity.h"

class GameEntityPrivate {
public:
    std::string mName;
    std::vector<std::string> mMovesVec;
};

GameEntity::GameEntity()
    :mpPrivate(std::make_unique<GameEntityPrivate>())
{
    mpPrivate->mName = "";
}
GameEntity::GameEntity(const std::string& kName, const std::vector<std::string>& kMovesVec)
    : mpPrivate(std::make_unique<GameEntityPrivate>())
{
    setName(kName);
    mpPrivate->mMovesVec = kMovesVec;
}

void GameEntity::setName(const std::string& kName) {
    mpPrivate->mName;
}
std::string GameEntity::getName() const {
    return mpPrivate->mName;
}

void GameEntity::addMove(const std::string& kMove) {
    mpPrivate->mMovesVec.push_back(kMove);

}
std::vector<std::string> GameEntity::getMoves() const {
    return mpPrivate->mMovesVec;
}
