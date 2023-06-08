/**************************************************************
 * File : moveDao.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: Header file defining the MoveDao class, which is responsible for
 * data access operations related to games.
 *************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <string>

 // Forward declarations of classes.
class FileReader;
class MoveDataParser;
class MoveEntity;
class MoveDaoPrivate;

class MoveDao {
public:
    /**
     * Intent : Constructor for the MoveDao class
     * Pre: A FileReader and a MoveDataParser must exist before creating a MoveDao instance.
     * Post: A new MoveDao object is created with the given FileReader and MoveDataParser.
     * \param kFileReader A shared_ptr to a FileReader instance.
     * \param kMoveDataParser A shared_ptr to a MoveDataParser instance.
     * \return A MoveDao object.
     */
    MoveDao(const std::shared_ptr<FileReader>& kFileReader, const std::shared_ptr<MoveDataParser>& kMoveDataParser);

    /**
     * Intent : Destructor for the MoveDao class
     * Pre: A MoveDao object must exist.
     * Post: The MoveDao object is destroyed and its resources are released.
     * \return None.
     */
    ~MoveDao();

    /**
     * Intent : Retrieve move data from a given file path
     * Pre: A valid file path must be provided.
     * Post: Move data from the file at the provided path is retrieved and parsed.
     * \param kFilePath A string representing the file path to the move data.
     * \return A vector containing MoveEntity objects, representing the parsed move data.
     */
    std::vector<MoveEntity> getData(const std::string& kFilePath);

private:
    // Private class data to encapsulate implementation details and improve information hiding.
    std::unique_ptr<MoveDaoPrivate> mpPrivate;
};
