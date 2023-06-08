
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
    mpPrivate->player = std::make_unique<QMediaPlayer>();
}

MusicMode::~MusicMode() {}

void MusicMode::playMusic(const std::string& kMusicFilePath) {
    mpPrivate->player->setMedia(QUrl::fromLocalFile(QString::fromStdString(kMusicFilePath)));

    mpPrivate->player->setVolume(100);
    mpPrivate->player->play();



}
