#include "shortcutpage.h"

#include <QDebug>

ShortCutPage::ShortCutPage(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout;
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

    layout->addWidget(newLabel, 0, 0);
    layout->addWidget(newLineEdit, 0, 1);
    layout->addWidget(openLabel, 0, 2);
    layout->addWidget(openLineEdit, 0, 3);
    layout->addWidget(saveLabel, 1, 0);
    layout->addWidget(saveLineEdit, 1, 1);
    layout->addWidget(saveAsLabel, 1, 2);
    layout->addWidget(saveAsLineEdit, 1, 3);
    layout->addWidget(closeLabel, 2, 0);
    layout->addWidget(closeLineEdit, 2, 1);
    layout->addWidget(copyLabel, 2, 2);
    layout->addWidget(copyLineEdit, 2, 3);
    layout->addWidget(cutLabel, 3, 0);
    layout->addWidget(cutLineEdit, 3, 1);
    layout->addWidget(pasteLabel, 3, 2);
    layout->addWidget(pasteLineEdit, 3, 3);

    layout->addWidget(undoLabel, 4, 0);
    layout->addWidget(undoLineEdit, 4, 1);
    layout->addWidget(redoLabel, 4, 2);
    layout->addWidget(redoLineEdit, 4, 3);

    layout->addWidget(printLabel, 5, 0);
    layout->addWidget(printLineEdit, 5, 1);
    layout->setSpacing(16);

//    connect(newLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(openLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(saveLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(saveAsLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(closeLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(copyLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(cutLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(pasteLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(undoLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(redoLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);
//    connect(printLineEdit, &QLineEdit::textChanged, this, &SettingDialog::buttonStatus);

    setup();
    setLayout(layout);
}

ShortCutPage::~ShortCutPage()
{

}

void ShortCutPage::setup()
{
    QString settingFilePath = QDir::currentPath() + "/setting.ini";
    QSettings setting(settingFilePath, QSettings::IniFormat);

    qDebug() << setting.allKeys().size();
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
