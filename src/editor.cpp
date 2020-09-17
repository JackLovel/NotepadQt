#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    setup();
}


Editor::~Editor()
{

}


void Editor::setup()
{
    fileSuffix = " "; // 初始化文件后缀
    fileName = "空白文档";
    filePath = " ";

    setAcceptDrops(false);

    // 默认的 tab 为 4
    setTabWidth(4);
}

void Editor::wheelEvent(QWheelEvent *e)
{
        if ((QApplication::keyboardModifiers() == Qt::ControlModifier )
                && (e->delta() > 0))
        {
            this->zoomIn();
        }
        else if ((QApplication::keyboardModifiers() == Qt::ControlModifier )
                 && (e->delta() < 0))
        {
            this->zoomOut();
        }
        else if (e->delta() < 0) {

        }
        else if (e->delta() > 0) {

        }
}


void Editor::copy()
{
    QTextEdit::copy();
}

void Editor::cut()
{
    QTextEdit::cut();
}


void Editor::paste()
{
    QTextEdit::paste();
}

void Editor::undo()
{
    QTextEdit::undo();
}


void Editor::redo()
{
    QTextEdit::redo();
}

void Editor::setFontUnderline()
{
    if (!underLineDone)
    {
        underLineDone = true;
    }
    else
    {
        underLineDone = false;
    }

    QTextEdit::setFontUnderline(underLineDone);
}


void Editor::setFontItalic()
{
    if (!italicDone)
    {
        italicDone = true;
    }
    else
    {
        italicDone = false;
    }

    QTextEdit::setFontItalic(italicDone);
}


void Editor::setFontBold()
{
    if (!boldDone)
    {
        boldDone = true;
    }
    else
    {
        boldDone = false;
    }

    qint32 font = boldDone ? QFont::Bold : QFont::Normal;
    QTextEdit::setFontWeight(font);
}


void Editor::setText(const QString text)
{
    QTextEdit::setText(text);
}


void Editor::open(const QString path)
{
    if (path.isEmpty()) {
        return;
    }
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString text = file.readAll();
    setText(text);

    file.close();
}


void Editor::save(const QString path)
{
    if (path.isEmpty()) {
        return;
    }
    QString text = this->toPlainText();

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(text.toUtf8());
    file.close();
}


void Editor::saveAs(const QString path)
{
    if (path.isEmpty()) {
        return;
    }
    QString content = this->toPlainText();

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(content.toUtf8());
    file.close();
}


void Editor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    QAction *undo = menu->addAction(tr("撤消(&U)"), this, SLOT(undo()), QKeySequence::Undo);
    undo->setEnabled(document()->isUndoAvailable());

    QAction *redo = menu->addAction(tr("恢复(&R)"), this, SLOT(redo()),
                                    QKeySequence::Redo);
    redo->setEnabled(document()->isRedoAvailable());
    menu->addSeparator();

    QAction *cut = menu->addAction(tr("剪切(&T)"), this, SLOT(cut()), QKeySequence::Cut);
    cut->setEnabled(textCursor().hasSelection());


    QAction *copy = menu->addAction(tr("复制(&C)"), this,
                                    SLOT(copy()), QKeySequence::Copy);

    copy->setEnabled(textCursor().hasSelection());

    QAction *clear = menu->addAction(tr("清空"), this, SLOT(clear()));
    clear->setEnabled(!document()->isEmpty());

    QAction *select = menu->addAction(tr("全选"), this, SLOT(selectAll()), QKeySequence::SelectAll);
    select->setEnabled(!document()->isEmpty());

    menu->exec(event->globalPos());
    delete menu;
}

QMap<QString, QString> Editor::showTextRowAndCol()
{
    QMap<QString, QString> lineNumber;

    QTextCursor *textCursor = new QTextCursor(this->textCursor());

    QString rowCount = QString::number(textCursor->blockNumber() + 1);
    QString colCount = QString::number(textCursor->columnNumber() + 1);
    lineNumber.insert("col", colCount);
    lineNumber.insert("row", rowCount);

    return lineNumber;
}

void Editor::setFontSize(QString value)
{
    /* 设置编辑器内容区 字体大小 */
    qreal size = value.toDouble();

    this->setFontPointSize(size);
}

void Editor::setTabWidth(int tabStop)
{
    /* 设置 tab 大小 */
    // 如里不设置，默认为 4
    QFontMetrics metrics(this->font()); // 获取字体宽度
    setTabStopDistance(tabStop * metrics.horizontalAdvance(' '));
}
