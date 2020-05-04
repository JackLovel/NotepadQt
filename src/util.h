#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QDir>
#include <QSettings>

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

    static QMap<QString, QString> getRectFiles();
    static QString getProjectDir();
};

#endif // UTIL_H
