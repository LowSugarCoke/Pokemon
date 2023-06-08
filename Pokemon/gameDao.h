/**************************************************************
 * File : gameDao.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: Header file defining the GameDao class, which is responsible for
 *              data access operations related to games.
 *************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>

class FileReader;
class GameDataParser;
class GameEntity;
class GameDaoPrivate;
class GameDao {
public:

    /**
     * Intent : Constructor for the GameDao class
     * Pre: A FileReader and a GameDataParser must exist before creating a GameDao instance.
     * Post: A new GameDao object is created with the given FileReader and GameDataParser.
     * \param kFileReader A shared_ptr to a FileReader instance.
     * \param kGameDataParser A shared_ptr to a GameDataParser instance.
     * \return A GameDao object.
     */
    GameDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<GameDataParser>& kGameDataParser);

    /**
     * Intent : Destructor for the GameDao class
     * Pre: A GameDao object must exist.
     * Post: The GameDao object is destroyed and its resources are released.
     * \return None.
     */
    ~GameDao();

    /**
     * Intent : Retrieve game data from a given file path
     * Pre: A valid file path must be provided.
     * Post: Game data from the file at the provided path is retrieved and parsed.
     * \param kFilePath A string representing the file path to the game data.
     * \return A pair of vectors, each containing GameEntity objects. The first vector contains the parsed game data,
     *         and the second vector contains any data that failed to parse.
     */
    std::pair<std::vector<GameEntity>, std::vector<GameEntity>> getData(const std::string& kFilePath);
private:
    // Private class data to encapsulate implementation details and improve information hiding.
    std::unique_ptr<GameDaoPrivate> mpPrivate;
};
