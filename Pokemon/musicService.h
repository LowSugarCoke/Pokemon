#pragma once

#include <memory>
#include <string>

class MusicMode;
class MusicServicePrivate;
class MusicService {
public:

    MusicService(std::shared_ptr<MusicMode> pMusicMode);
    MusicService(const MusicService& kMusicService);
    ~MusicService();
    void playMusic(const std::string& kMusicFilePath);

private:
    std::unique_ptr<MusicServicePrivate> mpPrivate;
};
