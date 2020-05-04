#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initUI();
}

MainWindow::~MainWindow()
{

}


void MainWindow::initUI()
{
    find = true;
    setAcceptDrops(true); // allow MainWindow drop

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setTabsClosable(true);

    Editor *editor = new Editor;
    m_tabWidget->addTab(editor, "空白文档");

    exitAct = new QAction("退出", this);
    exitAct->setObjectName("exit");
    newAct = new QAction("新建", this);
    newAct->setObjectName("newfile");
    openAct = new QAction("打开", this);
    openAct->setObjectName("openfile");
    saveAct = new QAction( "保存", this);
    saveAct->setObjectName("savefile");
    saveAsAct = new QAction("保存为", this);
    saveAsAct->setObjectName("print");
    printAct = new QAction("打印", this);
    printAct->setObjectName("print");
    copyAct = new QAction("拷贝", this);
    copyAct->setObjectName("copy");
    cutAct = new QAction("剪切", this);
    cutAct->setObjectName("cut");
    pasteAct = new QAction("粘贴", this);
    pasteAct->setObjectName("paste");
    undoAct = new QAction("撤销", this);
    undoAct->setObjectName("undo");
    redoAct = new QAction("重做", this);
    redoAct->setObjectName("redo");
    fontAct = new QAction("字体设置", this);
    boldAct = new QAction("加粗", this);
    underlineAct = new QAction("下划线", this);
    fontItalicAct = new QAction("斜体", this);
    aboutAct = new QAction("关于", this);
    settingAct = new QAction("设置", this);
    updateAct = new QAction("更新", this);

    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(settingAct);
    fileMenu->addAction(exitAct);

    QMenu *editMenu = menuBar()->addMenu(tr("编辑"));
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(fontAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(aboutAct);

    connect(exitAct, &QAction::triggered, this, &MainWindow::exitSlot);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::aboutDialogSlot);
    connect(newAct, &QAction::triggered, this, &MainWindow::newDocumentSlot);
    connect(openAct, &QAction::triggered, this, &MainWindow::openSlot);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveSlot);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveSlot);
    connect(printAct, &QAction::triggered, this, &MainWindow::printSlot);
    connect(fontAct, &QAction::triggered, this, &MainWindow::selectFont);
    connect(m_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));
    connect(settingAct, &QAction::triggered, this, &MainWindow::openSettingDialog);
    connect(getEditor(), &QTextEdit::cursorPositionChanged, this, &MainWindow::showStausLineNumber);

    resize(Util::readSetting("userCustom", "size").toSize());
    move(Util::readSetting("userCustom", "pos").toPoint());

    settingDialog = new SettingDialog;

    findAct = new QAction(tr("查找"));
    fileMenu->addAction(findAct);
    findDialog = new FindDialog;

    replaceAction = new QAction(tr("替换"));
    fileMenu->addAction(replaceAction);
    replaceDialog = new ReplaceDialog;

    connect(findAct, &QAction::triggered, this, [=]() {
        findDialog->exec();
    });

    connect(replaceAction, &QAction::triggered, this, [=]() {
        replaceDialog->exec();
    });

    connect(findDialog, SIGNAL(sendQueryText(QString, bool, bool)),
    this,SLOT(findSlot(QString, bool, bool)));

    connect(replaceDialog, SIGNAL(findReplaceStr(QString,bool)),
    this,SLOT(findReplace(QString,bool)));
    connect(replaceDialog, SIGNAL(replaceCurOneStr(QString, QString)),
    this,SLOT(replaceCur(QString, QString)));
    connect(replaceDialog, SIGNAL(replaceAllStr(QString, QString, bool)),
    this,SLOT(replaceAll(QString, QString, bool)));

    connect(settingDialog, &SettingDialog::sendCustomConfig, this, &MainWindow::setCustomConfig);

    // 跳转行
    QAction *goLineAction = new QAction("跳转行");
    fileMenu->addAction(goLineAction);
    GoLineDialog *goLineDialog = new GoLineDialog();
    connect(goLineAction, &QAction::triggered, this, [=]() {
        goLineDialog->exec();
    });

    // md5 dialog
    QMenu *toolMenu = menuBar()->addMenu(tr("工具"));
    Md5Dialog *md5Dialog = new Md5Dialog();
    QAction *stringMd5Action = new QAction("从字符生成");
    toolMenu->addAction(stringMd5Action);
    connect(stringMd5Action, &QAction::triggered, this, [=]() {
        md5Dialog->exec();
    });

    connect(goLineDialog, SIGNAL(sendLineNumber(int)), this, SLOT(goLineSlot(int)));

    initTray();
    initShortCutKey();
    initStatusBar();
    setWindowTitle(tr("Notepad"));
    setCentralWidget(m_tabWidget);

    connect(tabSizeCombox, SIGNAL(activated(QString)), this, SLOT(setTabToWidth(QString)));


    recentFileMenu = new QMenu("最近的文件");
    loadRectFiles();
    menuBar()->addMenu(recentFileMenu);
}

void MainWindow::exitSlot()
{
    qApp->quit();
}

Editor* MainWindow::getEditor(){
    Editor *e = static_cast<Editor*>(m_tabWidget->currentWidget());
    return e;
}

void MainWindow::setFileSuffix(QString suffix)
{
//    qDebug() << Util::getFileTypeMap();

    QString description = Util::getFileTypeMap()[suffix];

//    qDebug() << description;
    fileTypeLabel->setText(description);
}

void MainWindow::openSlot()
{
    QString tabName;
    int index;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "open file");
    getEditor()->open(fileName);

    if (fileName.isEmpty()) {
        index = 0;
        tabName = "空白文档";
    } else {
        index = m_tabWidget->currentIndex();
        tabName = fileName.split("/").last();
    }

    QString suffix = getEditor()->fileSuffix = fileName.split(".").last();
    //qDebug() << suffix;
    setFileSuffix(suffix);

    m_tabWidget->setTabText(index, tabName);
}

void MainWindow::saveSlot()
{
    QString fileName;
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "保存");
        currentFile = fileName;
    }
    else
    {
        fileName = currentFile;
    }

    qDebug() << fileName;

    getEditor()->save(fileName);
    setWindowTitle(fileName);
}

void MainWindow::saveAsSlot()
{
    QString fileName = QFileDialog
            ::getSaveFileName(this, "Save as");

//    qDebug() << "文件的路径:" << fileName;
    setWindowTitle(fileName);
    getEditor()->saveAs(fileName);
}

void MainWindow::printSlot()
{
    QPrinter printDev;
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
    {
        return;
    }
    getEditor()->print(&printDev);
}

void MainWindow::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected){
        Editor *e = static_cast<Editor*>(m_tabWidget->currentWidget());
        e->setFont(font);
    }
}

void MainWindow::initTray()
{
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(QIcon(":/img/ico.svg"));
    systemTray->setToolTip(tr("K记事本"));

    // create menu
    QMenu *trayMenu = new QMenu(this);
    trayMenu->addAction(aboutAct);
    trayMenu->addAction(fontAct);
    trayMenu->addSeparator();
    trayMenu->addAction(updateAct);
    trayMenu->addAction(settingAct);
    trayMenu->addAction(exitAct);

    systemTray->setContextMenu(trayMenu);
    systemTray->show();

    connect(systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}


void MainWindow::newDocumentSlot()
{
    Editor *editor = new Editor;
    m_tabWidget->addTab(editor, "空白文档");
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        break;
    default:
        break;
    }
}

void MainWindow::aboutDialogSlot()
{
    QMessageBox::about(this,
                       tr("关于"),
                       tr( "一个记事本<br>"
                           "作者：叶落初冬<br>"
                           "版本: &nbsp;&nbsp;v1.0"));
}

void MainWindow::removeSubTab(int index)
{
    int count = m_tabWidget->count();
    if (count == 1) {
        qApp->exit();
    }

    /* 关闭 tabWidget 标题 */
    m_tabWidget->removeTab(index);
}

void MainWindow::openSettingDialog()
{
    settingDialog->show();
}

void MainWindow::setDefaultKey()
{
    QMap<QString, QString> keyMap = Util::getKeyMap();
    copyAct->setShortcut(keyMap[copyAct->objectName()]);
    cutAct->setShortcut(keyMap[cutAct->objectName()]);
    exitAct->setShortcut(keyMap[exitAct->objectName()]);
    newAct->setShortcut(keyMap[newAct->objectName()]);
    openAct->setShortcut(keyMap[openAct->objectName()]);
    pasteAct->setShortcut(keyMap[pasteAct->objectName()]);
    printAct->setShortcut(keyMap[printAct->objectName()]);
    redoAct->setShortcut(keyMap[redoAct->objectName()]);
    undoAct->setShortcut(keyMap[undoAct->objectName()]);
    saveAsAct->setShortcut(keyMap[saveAsAct->objectName()]);
    saveAct->setShortcut(keyMap[saveAct->objectName()]);
}

void MainWindow::initShortCutKey()
{
    QSettings setting(settingFile, QSettings::IniFormat);

    // 如果不包含自定义配置，那就使用默认配置
    if (!Util::configExist("custom")) {
        setDefaultKey();
        return;
    }
    setting.beginGroup("custom");
    exitAct->setShortcut(setting.value("closeWindow").toString());
    copyAct->setShortcut(setting.value("copy").toString());
    cutAct->setShortcut(setting.value("cut").toString());
    newAct->setShortcut(setting.value("newFile").toString());
    openAct->setShortcut(setting.value("openFile").toString());
    pasteAct->setShortcut(setting.value("paste").toString());
    redoAct->setShortcut(setting.value("redo").toString());
    saveAct->setShortcut(setting.value("saveFile").toString());
    saveAsAct->setShortcut(setting.value("saveAsFile").toString());
    undoAct->setShortcut(setting.value("undo").toString());
    printAct->setShortcut(setting.value("print").toString());
    setting.endGroup();
}

void MainWindow::initStatusBar()
{
    tabSizeCombox = new QComboBox();
    tabSizeCombox->addItem("4");
    tabSizeCombox->addItem("2");

//    QComboBox *encodeCombox = new QComboBox();

//    encodeCombox->addItem("utf8");
//    encodeCombox->addItem("gbk");

    lineNumberLabel = new QLabel();
    //QLabel *m_secondStatusLabel = new QLabel(tr("测试标签"));
    //this->statusBar()->addWidget(m_secondStatusLabel, 1);
//    this->statusBar()->addWidget(m_secondStatusLabel1, 1);

    fileTypeLabel = new QLabel();

    this->statusBar()->addWidget(fileTypeLabel, 8);
    this->statusBar()->addWidget(lineNumberLabel, 4);
    this->statusBar()->addWidget(tabSizeCombox);
    //this->statusBar()->addWidget(encodeCombox);

    //m_secondStatusLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::showStausLineNumber()
{
    QMap<QString, QString> lineNumber = getEditor()->showTextRowAndCol();

    QString row = lineNumber.value("row");
    QString col = lineNumber.value("col");
    lineNumberLabel->setText(QString("第%1列,第%2列").arg(row, col));

    this->statusBar()->addWidget(lineNumberLabel);
    lineNumberLabel->setAlignment(Qt::AlignLeft);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    bool ok = QMessageBox::question(this, tr("退出"), tr("退出应用?"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes) == QMessageBox::Yes;
    if (ok) {
        QSettings setting(settingFile, QSettings::IniFormat);
        setting.beginGroup("userCustom");
        setting.setValue("pos", pos());
        setting.setValue("size", size());
        setting.endGroup();
        e->accept();
    } else {
        e->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list")) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    QList<QUrl> urls = e->mimeData()->urls();
    // 列表不为空，可能有多个文件
    if (urls.isEmpty()) {
        return;
    }

    // 取出第一个文件
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    getEditor()->setText(Util::readFile(fileName));
}

void MainWindow::findSlot(QString str, bool ignore, bool choose)
{
    QString text = str;
    bool find_flag;
    if (!text.isEmpty()) {
        if (choose) {
            if (ignore) {
                find_flag = getEditor()->find(text, QTextDocument::FindCaseSensitively);
            } else {
                find_flag = getEditor()->find(text);
            }
        } else {
            if (ignore) {
                find_flag = getEditor()->find(text,
                            QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
            } else {
                find_flag = getEditor()->find(text,
                            QTextDocument::FindBackward);
            }
        }

        if (!find_flag)
            QMessageBox::information(this, tr("结果"), tr("没有找到"), QMessageBox::Yes);
    }
}

void MainWindow::findReplace(QString find_str, bool flg)
{
    bool find_flag;
    if (flg) {
        find_flag = getEditor()->find(find_str, QTextDocument::FindCaseSensitively);
    } else {
        find_flag = getEditor()->find(find_str);
    }

    if (!find_flag) {
        QMessageBox::information(this, tr("结果"), tr("没有找到查找内容"), QMessageBox::Yes);
    } else {
        find = true;
    }
}

void MainWindow::replaceCur(QString find_str,QString replace_str)
{
    bool find = getEditor()->find(find_str);
    if (find) {
        QTextCursor textCursor = getEditor()->textCursor();
        textCursor.insertText(replace_str);
    } else {
        QMessageBox::information(this, tr("结果"), tr("没有找到内容")+find_str, QMessageBox::Yes);
    }
}

void MainWindow::replaceAll(QString find_str, QString replace_str, bool flg)
{
    if (!flg) {
        bool haf = getEditor()->find(find_str);

        if (haf) {
            QTextCursor textCursor = getEditor()->textCursor();
            textCursor.insertText(replace_str);

            while(getEditor()->find(find_str)) {
                textCursor = getEditor()->textCursor();
                textCursor.insertText(replace_str);
            }

            while(getEditor()->find(find_str, QTextDocument::FindBackward)) {
                textCursor = getEditor()->textCursor();
                textCursor.insertText(replace_str);
            }
        } else {
            QMessageBox::information(this, tr("结果"), tr("没有内容不能替换")+find_str, QMessageBox::Yes);
        }
    } else {
        bool haf = getEditor()->find(find_str, QTextDocument::FindCaseSensitively);
        if (haf) {
            QTextCursor textCursor = getEditor()->textCursor();
            textCursor.insertText(replace_str);
            while(getEditor()->find(find_str, QTextDocument::FindCaseSensitively)) {
                textCursor = getEditor()->textCursor();
                textCursor.insertText(replace_str);
            }

            while (getEditor()->find(find_str, QTextDocument::FindCaseSensitively|QTextDocument::FindBackward)) {
                textCursor = getEditor()->textCursor();
                textCursor.insertText(replace_str);
            }
        } else {
            QMessageBox::information(this, tr("结果"), tr("没有内容不能替换") + find_str, QMessageBox::Yes);
        }
    }
}

void MainWindow::setCustomConfig()
{
    QSettings setting(settingFile, QSettings::IniFormat);

    // 加载自定义配置
    setting.beginGroup("custom");
    exitAct->setShortcut(setting.value("closeWindow").toString());
    copyAct->setShortcut(setting.value("copy").toString());
    cutAct->setShortcut(setting.value("cut").toString());
    newAct->setShortcut(setting.value("newFile").toString());
    openAct->setShortcut(setting.value("openFile").toString());
    pasteAct->setShortcut(setting.value("paste").toString());
    redoAct->setShortcut(setting.value("redo").toString());
    saveAct->setShortcut(setting.value("saveFile").toString());
    saveAsAct->setShortcut(setting.value("saveAsFile").toString());
    undoAct->setShortcut(setting.value("undo").toString());
    printAct->setShortcut(setting.value("print").toString());
    setting.endGroup();
}

void MainWindow::goLineSlot(int lineNumber)
{
    //@http://outofmemory.cn/code-snippet/259/TextEdit-tiaozhuan-come-specify-row-jiejuefangan
    Editor *e = getEditor();
    QTextCursor cursor = e->textCursor();
    int position = e->document()
            ->findBlockByNumber(lineNumber - 1).position();

    cursor.setPosition(position, QTextCursor::MoveAnchor);
    e->setTextCursor(cursor);
}

void MainWindow::setTabToWidth(QString widthText)
{
    // set current editor tab size
    int tabWidth = widthText.toInt();

    Editor *e = getEditor();
    e->setTabWidth(tabWidth);
}

void MainWindow::loadRectFiles()
{
    auto maps = Util::getRectFiles();
    for(auto k: maps.keys())
    {
        auto v = maps[k];
        recentFileMenu->addAction(QString("%2").arg(v));
    }

//    auto actionList = recentFileMenu->actions();
//    for(auto a : actionList) {
//        connect(a, &QAction::triggered, [=]{

//           auto path = a->text();
//           QString content = Util::readFile(path);
////           ui->textEdit->setText(content); // 点击后执行的操作
//        });
//    }
}




