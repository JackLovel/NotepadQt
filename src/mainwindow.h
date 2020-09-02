#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editor.h"
#include "util.h"
//#include "configdialog.h"
#include "settingdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "golinedialog.h"
#include "md5dialog.h"

#include <QWidget>
#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QLabel>
#include <QMenu>
#include <QCloseEvent>
#include <QObject>
#include <QPixmap>
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QtPrintSupport>
#include <QPrintDialog>
#include <QPrinter>
#include <QFont>
#include <QFontDialog>
#include <QAction>
#include <QTextEdit>
#include <QCoreApplication>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QWheelEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QDebug>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QObject>
#include <QDragEnterEvent>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadRectFiles();

    void initStatus();
protected:
    void closeEvent(QCloseEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override; // 拖动
    void dropEvent(QDropEvent *e) override; // 释放

public slots:
   void exitSlot();
   void aboutDialogSlot();
   void newDocumentSlot();
   void iconActivated(QSystemTrayIcon::ActivationReason);
   void openSlot();
   void saveSlot();
   void saveAsSlot();
   void printSlot();
   void selectFont();
   void removeSubTab(int index);
   void openSettingDialog();
   void showStausLineNumber();
   void findSlot(QString, bool, bool);
   void findReplace(QString, bool); // replace
   void replaceCur(QString, QString);
   void replaceAll(QString, QString, bool);
   void setCustomConfig();
   void goLineSlot(int);
   void autoSaveSlot();

   //
   void setTabToWidth(QString);

   // treeView
   void openFileTreeView(const QModelIndex &index);

private:
    bool find;
    QSystemTrayIcon *systemTray;
    QTabWidget *m_tabWidget;
    QString currentFilePath;
    QLabel *lineNumberLabel;  // 行号显示
    FindDialog *findDialog;
    ReplaceDialog *replaceDialog;
    SettingDialog *settingDialog;
    QComboBox *tabSizeCombox;
    QLabel *fileTypeLabel;
    void setFileSuffix(QString suffix);

    bool boldDone = false;
    bool italicDone = false;
    bool underLineDone = false;
    int saveTime;

    QAction *newAct;
    QAction *exitAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *cutAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *fontAct;
    QAction *boldAct;
    QAction *underlineAct;
    QAction *fontItalicAct;
    QAction *aboutAct;
    QAction *settingAct;
    QAction *updateAct;
    QAction *findAct;
    QAction *replaceAction;
    QAction *autoSaveAction;

    // treeview, open folder
    QAction *openFolderAct;
    QFileSystemModel fileSystemModel;

    QString treeViewPath = nullptr;

    void initTray();
    void initUI();
    void initStatusBar();
    Editor *getEditor();
    void initShortCutKey();
    void setDefaultKey();

    QString  settingFile = QDir::currentPath() + "/setting.ini";

    QMenu *recentFileMenu;

    // debug
    void debug();

    QTreeView *fileTreeView;
    QWidget *mainWidget;
    QHBoxLayout *mainLayout;
    QAction *treeViewAction;
};

#endif // MAINWINDOW_H
