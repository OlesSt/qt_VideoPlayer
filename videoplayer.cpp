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
    mediaPlayer->setVideoOutput(videoWidget);
    ui->videoFrame->addWidget(videoWidget);

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &VideoPlayer::stateChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);

    connect(ui->pushPlay, SIGNAL(clicked(bool)), this, SLOT(pushPlay()));
    connect(ui->pushPause, SIGNAL(clicked(bool)), this, SLOT(pushPause()));
    connect(ui->pushStop, SIGNAL(clicked(bool)), this, SLOT(pushStop()));
    connect(ui->pushMute, SIGNAL(clicked(bool)), this, SLOT(pushMute()));

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(fileOpen()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(fileExit()));

    connect(ui->sliderTiming, SIGNAL(sliderMoved(int)), this, SLOT(sliderTiming_Moved(int)));
    connect(ui->sliderVolume, SIGNAL(sliderMoved(int)), this, SLOT(sliderVolume_Moved(int)));

}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::stateChanged(QMediaPlayer::PlaybackState state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        ui->pushPause->setEnabled(true);
        ui->pushPause->setEnabled(true);
        ui->pushStop->setEnabled(true);
    }
    else if (state == QMediaPlayer::PausedState)
    {
        ui->pushPlay->setEnabled(true);
        ui->pushPause->setEnabled(false);
        ui->pushStop->setEnabled(true);
    }
    else if (state == QMediaPlayer::StoppedState)
    {
        ui->pushPlay->setEnabled(true);
        ui->pushPause->setEnabled(false);
        ui->pushStop->setEnabled(false);
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    if (ui->sliderTiming->maximum() != mediaPlayer->duration())
        ui->sliderTiming->setMaximum(mediaPlayer->duration());
    ui->sliderTiming->setValue(position);

    int seconds = position/1000 % 60;
    int minut = seconds/60 % 60;
    int hours = minut/60 & 24;

    QTime time (hours, minut, seconds);
    ui->labelTiming->setText(time.toString());
}

void VideoPlayer::pushPlay()    {mediaPlayer->play();}
void VideoPlayer::pushPause()   {mediaPlayer->pause();}
void VideoPlayer::pushStop()    {mediaPlayer->stop();}

void VideoPlayer::pushMute()
{
    if (isMute)
    {
        audioOutput->setMuted(true);
        ui->pushMute->setText("Muted");
        isMute = false;
    }
    else
    {
        audioOutput->setMuted(false);
        ui->pushMute->setText("Mute");
        isMute = true;
    }
}

void VideoPlayer::fileOpen()
{
    QString filename = QFileDialog::getOpenFileName();
    QFileInfo fileInfo(filename);
    mediaPlayer->setSource(QUrl::fromLocalFile(filename));
    ui->pushPlay->setEnabled(true);
    ui->fileName->setText(fileInfo.fileName());
}

void VideoPlayer::fileExit()                        {this->close();}
void VideoPlayer::sliderVolume_Moved(int volume)    {audioOutput->setVolume(volume);}
void VideoPlayer::sliderTiming_Moved(int timing)    {mediaPlayer->setPosition(timing);}
