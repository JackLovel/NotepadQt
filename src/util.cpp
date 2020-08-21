#include "util.h"

#include <QFile>
#include <QWidget>
#include <QKeySequence>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QString>
#include <QMessageBox>
#include <QJsonArray>
#include <QDebug>
#include <QVariant>
#include <QDesktopWidget>
#include <QMap>
#include <QApplication>

void Util::loadStyleSheet(const QString &styleSheetFile, QWidget *widget)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = widget->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        widget->setStyleSheet(styleSheet);
        file.close();
    }
}

void Util::writeSetting(const QString &group, const QString &key, const QString &value)
{
    QString  settingFile = QDir::currentPath() + "/setting.ini";
    QSettings setting(settingFile, QSettings::IniFormat);

    setting.beginGroup(group);
    setting.setValue(key, value);
    setting.endGroup();
}

QVariant Util::readSetting(const QString &group, const QString &key)
{
    // 配置文件的路径
    static QString  settingFile = QDir::currentPath() + "/setting.ini";
    QSettings setting(settingFile, QSettings::IniFormat);
    setting.beginGroup(group);
    auto value =  setting.value(key);
    setting.endGroup();

    return value;
}

QString Util::readFile(const QString &fileName)
{
    QFile file(fileName);
    QString content;
    if (file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
    }

    return content;
}

// https://www.e-learn.cn/content/qita/2516998
// 用于解析 setting.json
QMap<QString, QString> Util::readJsonFile(const QString &filePath, const QString &key)
{
    QFile file;
    QString content;

    file.setFileName(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonDocument d = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject m_object = d.object(); // 转化为对象
//    QJsonValue m_value = m_object.value("defaultshortcuts");
    QJsonValue m_value = m_object.value(key);
    QJsonArray jsonArray = m_value.toArray();
    QMap<QString, QString> shortKeyMap;
    foreach (auto v, jsonArray) {
        QString name = v.toObject().value("key").toString();
        QString shortCut = v.toObject().value("default").toString();

//        qDebug() << "name:" << name << "shortCut" << shortCut;
        shortKeyMap.insert(name, shortCut);
    }

    return shortKeyMap;
}

static QString jsonFile = ":/config/setting.json";
QMap<QString, QString> Util::getKeyMap()
{
    return readJsonFile(jsonFile, "defaultshortcuts");
}

static QString filetypeFile = ":/config/filetype.json";
QMap<QString, QString> Util::getFileTypeMap()
{
    QFile file;
    QString content;

    file.setFileName(filetypeFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonDocument d = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject m_object = d.object(); // 转化为对象

    QJsonValue m_value = m_object.value("filetype");
    QJsonArray jsonArray = m_value.toArray();
    QMap<QString, QString> shortKeyMap;
    foreach (auto v, jsonArray) {
        QString name = v.toObject().value("suffix").toString();
        QString shortCut = v.toObject().value("type").toString();

//        qDebug() << "name:" << name << "shortCut" << shortCut;
        shortKeyMap.insert(name, shortCut);
    }

    return shortKeyMap;
}


static QString  settingFile = QDir::currentPath() + "/setting.ini";
bool Util::configExist(QString configName)
{
    QSettings setting(settingFile, QSettings::IniFormat);

    setting.beginGroup(configName);

    if (setting.contains("closeWindow") && setting.contains("undo")) {
        return true;
    }
    setting.endGroup();
    return false;
}

QString Util::getProjectDir() {
    return QDir::currentPath();
}

QString Util::getSplitLast(QString string, QString separator)
{
    return string.split(separator).last();
}

// 读取配置文件
QMap<QString, QString> Util::getRectFiles()
{
    QMap<QString, QString> map;
    QString file = "recentFiles.ini";
    QString  settingFile = getProjectDir() + "/" + file;

    QSettings setting(settingFile, QSettings::IniFormat);
    const QString group = "RectFile";
    setting.beginGroup(group);
    for(int i = 0; i < setting.allKeys().length(); i++) {
        QString k = setting.allKeys().at(i);
        QString v = setting.value(k).toString();
        map[k] = v;
    }
    setting.endGroup();

    return map;
}


void Util::setRectFiles(const QString &path)
{
    QString file = "recentFiles.ini";
    QString  settingFile = getProjectDir() + "/" + file;
    QSettings setting(settingFile, QSettings::IniFormat);

    const QString group = "RectFile";
    setting.beginGroup(group);
    setting.setValue(path, path);
    setting.endGroup();
}

// 获取桌面的分辨率
QSize Util::desktopSize() {

    auto desktop = QGuiApplication::screens()
            .first()->grabWindow(0);

    QSize size = desktop.size();

    return size;
}
