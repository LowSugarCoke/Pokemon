#pragma once

#include <memory>
#include <string>

class MusicModePrivate;
class MusicMode {
public:

    MusicMode();
    ~MusicMode();

    void playMusic(const std::string& kMusicFilePath);

private:
    std::unique_ptr<MusicModePrivate> mpPrivate;
};
