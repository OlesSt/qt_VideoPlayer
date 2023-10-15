#include "videoplayer.h"
#include "ui_videoplayer.h"

#include <QTime>
#include <QFileInfo>
#include <QFileDialog>

VideoPlayer::VideoPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    ui->sliderVolume->setMinimum(0);
    ui->sliderVolume->setMaximum(10);
    ui->sliderVolume->setValue(80);

    isMute = false;
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    videoWidget = new QVideoWidget();

    mediaPlayer->setAudioOutput(audioOutput);
    ui->videoFrame->addWidget(videoWidget);


}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::stateChanged(QMediaPlayer::PlaybackState state)
{

}

void VideoPlayer::positionChanged(qint64 position)
{

}

void VideoPlayer::pushPlay()    {mediaPlayer->play();}
void VideoPlayer::pushPause()   {mediaPlayer->pause();}
void VideoPlayer::pushStop()    {mediaPlayer->stop();}

void VideoPlayer::pushMute()    {}

void VideoPlayer::fileOpen()
{}
void VideoPlayer::fileExit()    {this->close();}

void VideoPlayer::sliderVolume_Moved(int volume) {audioOutput->setVolume(volume);}
void VideoPlayer::sliderTiming_Moved(int timing)
{

}
