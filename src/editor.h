#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QApplication>
#include <QWheelEvent>
#include <QFontDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMap>


class Editor : public QTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

    void setText(const QString text);
    void setFontUnderline();
    void setFontItalic();
    void setFontBold();

    void open(const QString path);
    void save(const QString path);
    void saveAs(const QString path);
    QMap<QString, QString> showTextRowAndCol();
    void setFontSize(QString fontSize);
    void setTabWidth(int length);
    void setup();

    QString fileSuffix;
    bool canSave = false; // 默认的，是不需要保存

    QString fileName;
    QString filePath;

signals:
    void cursorPositionChanged();

protected:
    void wheelEvent(QWheelEvent * event);
    void contextMenuEvent(QContextMenuEvent *e);



public slots:
    void copy();
    void cut();
    void paste();
    void undo();
    void redo();
    void saveStatusSlot();

private:
    bool boldDone = false;
    bool italicDone = false;
    bool underLineDone = false;
};
#endif // EDITOR_H
