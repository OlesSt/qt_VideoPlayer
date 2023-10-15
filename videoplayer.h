#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void stateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);

private slots:
    void pushPlay();
    void pushPause();
    void pushStop();
    void pushMute();
    void fileOpen();
    void fileExit();

    void sliderVolume_Moved(int volume);
    void sliderTiming_Moved(int timing);

private:
    Ui::VideoPlayer *ui;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QVideoWidget *videoWidget;
    bool isMute;
};

#endif // VIDEOPLAYER_H
