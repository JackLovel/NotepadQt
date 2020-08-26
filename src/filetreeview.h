#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H

#include <QObject>
#include <QStandardItem>
#include <QTreeView>

class FileTreeVIew : public QTreeView
{
    Q_OBJECT
public:
    FileTreeVIew();
    void iterateOverItems();
    QList<QStandardItem*> returnThenItems;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QStandardItemModel *model;
};

#endif // FILETREEVIEW_H
