#pragma once

#include <memory>
#include <string>

class PokemonLoggerPrivate;
class PokemonLogger {
public:
    static PokemonLogger& getInstance();
    void log(std::string logMessage);
    std::string getLog() const;
    void debug(std::string debugMessage);
    void addTurn();

private:
    PokemonLogger();
    ~PokemonLogger();
    std::unique_ptr<PokemonLoggerPrivate> mpPrivate;
};
