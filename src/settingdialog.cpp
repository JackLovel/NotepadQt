#include "settingdialog.h"
#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent)
{
   initUI();
}

SettingDialog::~SettingDialog()
{

}

void SettingDialog::initUI()
{
    shortCutPage = new ShortCutPage();
    advanceSettingPage = new  AdvanceSettingPage();

    QWidget *shortCutWidget = new QWidget();
    layout1 = new QGridLayout;
    newLabel = new QLabel(tr("新建："));
    newLineEdit = new QLineEdit;
    newLineEdit->setObjectName("newfile");
    openLabel = new QLabel(tr("打开："));
    openLineEdit = new QLineEdit;
    openLineEdit->setObjectName("openfile");
    saveLabel = new QLabel(tr("保存："));
    saveLineEdit = new QLineEdit;
    saveLineEdit->setObjectName("savefile");
    saveAsLabel = new QLabel(tr("保存为："));
    saveAsLineEdit = new QLineEdit;
    saveAsLineEdit->setObjectName("saveasfile");
    printLabel = new QLabel(tr("打印："));
    printLineEdit = new QLineEdit;
    printLineEdit->setObjectName("print");
    closeLabel = new QLabel(tr("退出："));
    closeLineEdit = new QLineEdit;
    closeLineEdit->setObjectName("exit");
    copyLabel = new QLabel(tr("拷贝："));
    copyLineEdit = new QLineEdit;
    copyLineEdit->setObjectName("copy");
    cutLabel = new QLabel(tr("剪切："));
    cutLineEdit = new QLineEdit;
    cutLineEdit->setObjectName("cut");
    pasteLabel = new QLabel(tr("粘贴："));
    pasteLineEdit = new QLineEdit;
    pasteLineEdit->setObjectName("paste");
    undoLabel = new QLabel(tr("撤销："));
    undoLineEdit = new QLineEdit;
    undoLineEdit->setObjectName("undo");
    redoLabel = new QLabel(tr("重做："));
    redoLineEdit = new QLineEdit;
    redoLineEdit->setObjectName("redo");

    layout1->addWidget(newLabel, 0, 0);
    layout1->addWidget(newLineEdit, 0, 1);
    layout1->addWidget(openLabel, 0, 2);
    layout1->addWidget(openLineEdit, 0, 3);
    layout1->addWidget(saveLabel, 1, 0);
    layout1->addWidget(saveLineEdit, 1, 1);
    layout1->addWidget(saveAsLabel, 1, 2);
    layout1->addWidget(saveAsLineEdit, 1, 3);
    layout1->addWidget(closeLabel, 2, 0);
    layout1->addWidget(closeLineEdit, 2, 1);
    layout1->addWidget(copyLabel, 2, 2);
    layout1->addWidget(copyLineEdit, 2, 3);
    layout1->addWidget(cutLabel, 3, 0);
    layout1->addWidget(cutLineEdit, 3, 1);
    layout1->addWidget(pasteLabel, 3, 2);
    layout1->addWidget(pasteLineEdit, 3, 3);

    layout1->addWidget(undoLabel, 4, 0);
    layout1->addWidget(undoLineEdit, 4, 1);
    layout1->addWidget(redoLabel, 4, 2);
    layout1->addWidget(redoLineEdit, 4, 3);

    layout1->addWidget(printLabel, 5, 0);
    layout1->addWidget(printLineEdit, 5, 1);
    layout1->setSpacing(16);


    shortCutWidget->setLayout(layout1);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(shortCutWidget, tr("快捷键"));
    m_tabWidget->addTab(shortCutPage, tr("快捷键"));
    m_tabWidget->addTab(advanceSettingPage, tr("高级配置"));

    okButton = new QPushButton(tr("确定"));
    okButton->setEnabled(false);
    defaultBtn = new QPushButton(tr("恢复默认"));
    cancelBtn = new QPushButton(tr("关闭"));

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch(1);
    btnLayout->addWidget(defaultBtn); // 恢复成默认设置
    btnLayout->addWidget(okButton);  // 保存当前设置
    btnLayout->addWidget(cancelBtn); // 退出当前窗口，且并不保存当前已改变的设置

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_tabWidget);
    mainLayout->addLayout(btnLayout);

    setupSetting();
    connect(defaultBtn, &QPushButton::clicked, this, &SettingDialog::defaultSetting);
    connect(cancelBtn, &QPushButton::clicked, this, &SettingDialog::closeWindow);
    connect(okButton, &QPushButton::clicked, this, &SettingDialog::customSetting);

    // init button status
    connect(newLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(openLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(saveLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(saveAsLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(closeLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(copyLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(cutLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(pasteLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(undoLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(redoLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
    connect(printLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);


    setLayout(mainLayout);
    setWindowTitle(tr("设置"));

}
// 关闭窗口
void SettingDialog::closeWindow()
{
    close();
}

// 启动时的配置
void SettingDialog::setupSetting()
{
    QSettings setting(settingFilePath, QSettings::IniFormat);

    // qDebug() << setting.allKeys().size();
    // 如果不存在自定义配置，就使用默认配置
    if (setting.contains("custom/newFile") && setting.contains("custom/redo")) {
        // 如果存在自定义配置，就使用自定义配置

        newLineEdit->setText(setting.value("custom/newFile").toString());
        openLineEdit->setText(setting.value("custom/openFile").toString());
        saveLineEdit->setText(setting.value("custom/saveFile").toString());
        saveAsLineEdit->setText(setting.value("custom/saveAsFile").toString());
        closeLineEdit->setText(setting.value("custom/closeWindow").toString());
        copyLineEdit->setText(setting.value("custom/copy").toString());
        cutLineEdit->setText(setting.value("custom/cut").toString());
        pasteLineEdit->setText(setting.value("custom/paste").toString());
        undoLineEdit->setText(setting.value("custom/undo").toString());
        redoLineEdit->setText(setting.value("custom/redo").toString());
        printLineEdit->setText(setting.value("custom/print").toString());

    } else {
        setting.beginGroup("default");

        setting.setValue("newFile", "ctrl+n");
        setting.setValue("openFile", "ctrl+o");
        setting.setValue("saveFile", "ctrl+s");
        setting.setValue("saveAsFile", "ctrl+shift+s");
        setting.setValue("closeWindow", "ctrl+q");
        setting.setValue("copy", "ctrl+c");
        setting.setValue("cut", "ctrl+x");
        setting.setValue("paste", "ctrl+v");
        setting.setValue("undo", "ctrl+z");
        setting.setValue("redo", "ctrl+shift+z");
        setting.setValue("print", "ctrl+p");
        setting.endGroup();

        newLineEdit->setText(setting.value("default/newFile").toString());
        openLineEdit->setText(setting.value("default/openFile").toString());
        saveLineEdit->setText(setting.value("default/saveFile").toString());
        saveAsLineEdit->setText(setting.value("default/saveAsFile").toString());
        closeLineEdit->setText(setting.value("default/closeWindow").toString());
        copyLineEdit->setText(setting.value("default/copy").toString());
        cutLineEdit->setText(setting.value("default/cut").toString());
        pasteLineEdit->setText(setting.value("default/paste").toString());
        undoLineEdit->setText(setting.value("default/undo").toString());
        redoLineEdit->setText(setting.value("default/redo").toString());
        printLineEdit->setText(setting.value("default/print").toString());
    }
}

// 自定义配置
void SettingDialog::customSetting()
{
    okButton->setEnabled(false);

//    // 把配置写到文件里
//    // void Util::writeSetting(const QString &group, const QString &key, const QString &value)
    Util::writeSetting("custom", "newFile", newLineEdit->text());
    Util::writeSetting("custom", "openFile", openLineEdit->text());
    Util::writeSetting("custom", "saveFile", saveLineEdit->text());
    Util::writeSetting("custom", "saveAsFile", saveAsLineEdit->text());
    Util::writeSetting("custom", "closeWindow", closeLineEdit->text());
    Util::writeSetting("custom", "copy", copyLineEdit->text());
    Util::writeSetting("custom", "cut", cutLineEdit->text());
    Util::writeSetting("custom", "paste", pasteLineEdit->text());
    Util::writeSetting("custom", "undo", undoLineEdit->text());
    Util::writeSetting("custom", "redo", redoLineEdit->text());
    Util::writeSetting("custom", "print", printLineEdit->text());

//    // 将数据发送到主窗口，将配置更新到最新的
//    // 或者加载文件里配置
    emit void sendCustomConfig();
}

// 恢复默认设置
void SettingDialog::defaultSetting()
{
    QMap<QString, QString> keyMap = Util::getKeyMap();

    copyLineEdit->setText(keyMap[copyLineEdit->objectName()]);
    cutLineEdit->setText(keyMap[cutLineEdit->objectName()]);
    closeLineEdit->setText(keyMap[cutLineEdit->objectName()]);
    newLineEdit->setText(keyMap[newLineEdit->objectName()]);
    openLineEdit->setText(keyMap[openLineEdit->objectName()]);
    pasteLineEdit->setText(keyMap[pasteLineEdit->objectName()]);
    printLineEdit->setText(keyMap[pasteLineEdit->objectName()]);
    redoLineEdit->setText(keyMap[redoLineEdit->objectName()]);
    saveAsLineEdit->setText(keyMap[saveAsLineEdit->objectName()]);
    saveLineEdit->setText(keyMap[saveLineEdit->objectName()]);
}

void SettingDialog::buttonStatus()
{
    okButton->setEnabled(true);
}
