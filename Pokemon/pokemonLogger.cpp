#include "pokemonLogger.h"

#include <vector>
#include <iostream>

class PokemonLoggerPrivate {
public:
    std::vector<std::string> mRecord;
    int mTurn;
};

PokemonLogger::PokemonLogger()
    : mpPrivate(std::make_unique<PokemonLoggerPrivate>())
{
    mpPrivate->mTurn = 1;
}

PokemonLogger& PokemonLogger::getInstance()
{
    static PokemonLogger instance; // Guaranteed to be destroyed, instantiated on first use.
    return instance;
}

PokemonLogger::~PokemonLogger() {

}

// Log a message with the current turn number
void PokemonLogger::log(std::string logMessage) {
    mpPrivate->mRecord.push_back("[Turn" + std::to_string(mpPrivate->mTurn) + "] " + logMessage);
}

// Retrieve the logged messages and clear the log
std::string PokemonLogger::getLog() const {
    std::string logger;
    auto record = mpPrivate->mRecord;
    for (int i = 0; i < record.size(); i++) {
        logger += record[i] + "\n";
    }
    mpPrivate->mRecord.clear();
    return logger;
}

// Log a debug message
void PokemonLogger::debug(std::string debugMessage) {
    std::cout << "[DEBUG] " << debugMessage << std::endl;
}

// Increment the turn number
void PokemonLogger::addTurn() {
    mpPrivate->mTurn++;
}
