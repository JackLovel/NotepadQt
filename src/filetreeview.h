#ifndef FileTreeView_H
#define FileTreeView_H

#include <QObject>
#include <QStandardItem>
#include <QTreeView>
#include <QFileSystemModel>

class FileTreeView : public QTreeView
{
    Q_OBJECT
public:
    FileTreeView();
    ~FileTreeView();

    QString path = nullptr;
    QFileSystemModel model;

    void loadView();

protected:

private:

};

#endif // FileTreeView_H
