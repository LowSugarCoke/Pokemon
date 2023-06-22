/**************************************************************
 * File : pokemonLogger.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file for the PokemonLogger class which provides logging functionality for the Pokemon game.
 *              It allows logging of messages, retrieving the log, debugging messages, and tracking the number of turns.
 *************************************************************/
#pragma once

#include <memory>
#include <string>

class PokemonLoggerPrivate;
class PokemonLogger {
public:

    /**
     * Intent : Get the instance of the PokemonLogger.
     * Pre: -
     * Post: Returns the instance of the PokemonLogger.
     * \return The instance of the PokemonLogger.
     */
    static PokemonLogger& getInstance();

    /**
     * Intent : Log a message.
     * Pre: logMessage is a valid log message.
     * Post: The log message is recorded.
     * \param logMessage The message to be logged.
     */
    void log(std::string logMessage);

    /**
     * Intent : Retrieve the current log.
     * Pre: -
     * Post: Returns the log as a string.
     * \return The log as a string.
     */
    std::string getLog() const;

    /**
     * Intent : Log a debug message.
     * Pre: debugMessage is a valid debug message.
     * Post: The debug message is recorded.
     * \param debugMessage The debug message to be logged.
     */
    void debug(std::string debugMessage);

    /**
     * Intent : Add a turn to the game.
     * Pre: -
     * Post: Increases the turn count by 1.
     */
    void addTurn();

private:
    /**
     * Intent : Constructs the PokemonLogger instance.
     * Pre: -
     * Post: The PokemonLogger instance is created.
     */
    PokemonLogger();

    /**
     * Intent : Destructor for the PokemonLogger class.
     * Pre: Instance of PokemonLogger exists.
     * Post: The PokemonLogger instance is properly destroyed.
     */
    ~PokemonLogger();

    std::unique_ptr<PokemonLoggerPrivate> mpPrivate;
};
