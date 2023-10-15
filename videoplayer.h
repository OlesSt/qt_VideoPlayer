#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

private:
    Ui::VideoPlayer *ui;
};

#endif // VIDEOPLAYER_H
