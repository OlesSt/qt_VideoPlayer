#include <QApplication>

#include "videoplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayer videoPlayer;
    videoPlayer.show();

    return a.exec();
}
