/**************************************************************
 * File : musicService.h
 * Author: Jack Lee
 * Create Date: 2023-06-08
 * Editor : Jack Lee
 * Update Date: 2023-06-08
 * Description: Header file for the MusicService class. This class
 *              provides services to play music.
 *************************************************************/
#pragma once

#include <memory>
#include <string>

class MusicMode;
class MusicServicePrivate;

class MusicService {
public:
    /**
     * Intent : Constructs a MusicService object with a given MusicMode.
     * Pre: pMusicMode should point to an existing MusicMode object.
     * Post: A MusicService object is created.
     * \param pMusicMode The shared pointer to a MusicMode object.
     */
    MusicService(std::shared_ptr<MusicMode> pMusicMode);

    /**
     * Intent : Copy constructor for MusicService object.
     * Pre: kMusicService is a valid, existing MusicService object.
     * Post: A new MusicService object is created as a copy of kMusicService.
     * \param kMusicService The MusicService object to copy.
     */
    MusicService(const MusicService& kMusicService);

    /**
     * Intent : Destroys the MusicService object.
     * Pre: The MusicService object exists.
     * Post: The MusicService object is destroyed, releasing any resources it was using.
     */
    ~MusicService();

    /**
     * Intent : Plays the music from the given file path.
     * Pre: kMusicFilePath should point to a valid music file.
     * Post: Music is played from the given file.
     * \param kMusicFilePath The path to the music file to be played.
     */
    void playMusic(const std::string& kMusicFilePath);

private:
    /**
     * A unique pointer to a MusicServicePrivate object, used for implementation details.
     */
    std::unique_ptr<MusicServicePrivate> mpPrivate;
};
