#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include "util.h"
#include "shortcutpage.h"
#include "advancesettingpage.h"

#include <QDialog>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QDir>
#include <QSettings>

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

signals:
    void sendCustomConfig();

private slots:
//    void setCustomSetting();
    void defaultSetting();
    void closeWindow();
    void customSetting();
    void buttonStatus();

private:
    /* 界面相关的 */
    QTabWidget *m_tabWidget;
    ShortCutPage *shortCutPage;
    AdvanceSettingPage *advanceSettingPage;

    /* 快捷键方式 */
    QWidget *shortCutWidget;
    QGridLayout *layout1;
    QLabel *newLabel;
    QLineEdit *newLineEdit;
    QLabel *openLabel;
    QLineEdit *openLineEdit;
    QLabel *saveLabel;
    QLineEdit *saveLineEdit;
    QLabel *saveAsLabel;
    QLineEdit *saveAsLineEdit;
    QLabel *printLabel;
    QLineEdit *printLineEdit;
    QLabel *closeLabel;
    QLineEdit *closeLineEdit;
    QLabel *copyLabel;
    QLineEdit *copyLineEdit;
    QLabel *cutLabel;
    QLineEdit *cutLineEdit;
    QLabel *pasteLabel;
    QLineEdit *pasteLineEdit;
    QLabel *undoLabel;
    QLineEdit *undoLineEdit;
    QLabel *redoLabel;
    QLineEdit *redoLineEdit;

    QPushButton *defaultBtn;
    QPushButton *okButton;
    QPushButton *cancelBtn;

    QString  settingFilePath = QDir::currentPath() + "/setting.ini";

    void setupSetting(); // 程序启动时的配置
    void setDefaultSetting();
    void initUI(); // 初始化界面
};

#endif // SETTINGDIALOG_H
