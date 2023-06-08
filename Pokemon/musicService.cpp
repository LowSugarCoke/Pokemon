#include "musicService.h"

#include "musicMode.h"

class MusicServicePrivate {
public:
    // Private constructor for MusicServicePrivate class
    MusicServicePrivate(std::shared_ptr<MusicMode> pMusicMode);

    std::shared_ptr<MusicMode> mpMusicMode;
};

// Constructor implementation for MusicServicePrivate class
MusicServicePrivate::MusicServicePrivate(std::shared_ptr<MusicMode> pMusicMode)
    : mpMusicMode(pMusicMode)
{

}

// Constructor implementation for MusicService class
MusicService::MusicService(std::shared_ptr<MusicMode> pMusicMode)
    : mpPrivate(std::make_unique<MusicServicePrivate>(pMusicMode))
{

}

// Copy constructor implementation for MusicService class
MusicService::MusicService(const MusicService& kMusicService)
    : mpPrivate(std::make_unique<MusicServicePrivate>(*kMusicService.mpPrivate))
{

}

// Destructor implementation for MusicService class
MusicService::~MusicService() {}

// Method to play music
void MusicService::playMusic(const std::string& kMusicFilePath) {
    mpPrivate->mpMusicMode->playMusic(kMusicFilePath);
}
