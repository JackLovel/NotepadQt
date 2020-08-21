#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // todo: 设置一个合理的窗体大小
    bool noUse = Util::getStatusSetting("noUse").toBool();
    if (noUse) {
        auto size = Util::desktopSize();
        auto width = size.width();
        auto height = size.height();
        w.resize(width / 2, height / 2);
        Util::putStatusSetting("noUse", "false");
    }

    w.show();

    return a.exec();
}
