#include "musicMode.h"

#include <QMediaPlayer>
#include <QUrl>

class MusicModePrivate {
public:
    std::unique_ptr<QMediaPlayer> player;
};

MusicMode::MusicMode()
    : mpPrivate(std::make_unique<MusicModePrivate>())
{
    mpPrivate->player = std::make_unique<QMediaPlayer>();  // Create a new QMediaPlayer instance
}

MusicMode::~MusicMode() {}

void MusicMode::playMusic(const std::string& kMusicFilePath) {
    mpPrivate->player->setMedia(QUrl::fromLocalFile(QString::fromStdString(kMusicFilePath)));
    // Set the media source for the player to the specified music file

    mpPrivate->player->setVolume(100);  // Set the volume of the player to 100 (maximum volume)
    mpPrivate->player->play();  // Start playing the music
}
