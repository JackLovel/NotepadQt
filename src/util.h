#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QDir>
#include <QSettings>
#include <QGuiApplication>
#include <QScreen>

class Util : public QObject
{
public:
    Util();
    ~Util();

    static void loadStyleSheet(const QString &qssName, QWidget *widget);

    // read and write config file
    static QVariant readSetting(const QString &group, const QString &key);
    static void writeSetting(const QString &group, const QString &key, const QString &value);

    static QString readFile(const QString &fileName);
//    static QKeySequence readJsonFile(QWidget *widget, const QString &fileAlias, const QString &key);
    static QMap<QString, QString> readJsonFile(const QString &filePath, const QString &key);
    static bool configExist(QString configName);
    static QMap<QString, QString> getKeyMap();
    static QMap<QString, QString> getFileTypeMap();

    // 最近文件功能相关
    static QString getProjectDir();
    static QMap<QString, QString> getRectFiles();
    static void setRectFiles(const QString &path);

    // 字符串处理
    static QString getSplitLast(QString string, QString separator);
    static QSize desktopSize();
};

#endif // UTIL_H
