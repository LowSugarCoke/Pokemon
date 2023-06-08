#include "musicService.h"

#include "musicMode.h"

class MusicServicePrivate {
public:
    MusicServicePrivate(std::shared_ptr<MusicMode> pMusicMode);

    std::shared_ptr<MusicMode> mpMusicMode;
};

MusicServicePrivate::MusicServicePrivate(std::shared_ptr<MusicMode> pMusicMode)
    :mpMusicMode(pMusicMode)
{

}


MusicService::MusicService(std::shared_ptr<MusicMode> pMusicMode)
    :mpPrivate(std::make_unique<MusicServicePrivate>(pMusicMode))
{

}
MusicService::MusicService(const MusicService& kMusicService)
    : mpPrivate(std::make_unique<MusicServicePrivate>(*kMusicService.mpPrivate))
{

}
MusicService::~MusicService() {}


void MusicService::playMusic(const std::string& kMusicFilePath) {
    mpPrivate->mpMusicMode->playMusic(kMusicFilePath);
}
