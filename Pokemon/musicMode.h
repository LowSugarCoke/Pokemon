/**************************************************************
 * File : musicMode.h
 * Author: ´å¶Ç´¼ B11130034
 * Create Date: 2023-06-08
 * Editor : ´å¶Ç´¼ B11130034
 * Update Date: 2023-06-08
 * Description: This header file defines the MusicMode class
 *              which is responsible for handling music-related
 *              functionality in an application.
 *************************************************************/
#pragma once

#include <memory>
#include <string>

class MusicModePrivate;
class MusicMode {
public:
    /**
     * Intent : Default constructor for MusicMode.
     * Pre: None.
     * Post: An instance of MusicMode is created.
     */
    MusicMode();

    /**
     * Intent : Destructor for MusicMode.
     * Pre: None.
     * Post: The MusicMode instance is properly destroyed.
     */
    ~MusicMode();

    /**
     * Intent : Function to play a music file.
     * Pre: The file path provided must point to a valid music file.
     * Post: The music file specified by the file path is played.
     * \param kMusicFilePath A string representing the file path of the music file to play.
     */
    void playMusic(const std::string& kMusicFilePath);

private:
    /**
     * Intent: A unique pointer to a MusicModePrivate instance.
     * This instance is used for encapsulating the implementation details of MusicMode (PIMPL idiom).
     */
    std::unique_ptr<MusicModePrivate> mpPrivate;
};
