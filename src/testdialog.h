#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include <QAbstractItemModel>

#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStandardItem>
#include <QTreeView>

namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = nullptr);
    ~TestDialog();

    void setSourceModel(QAbstractItemModel *model);
    void addMail(QAbstractItemModel *model, const QString &name, const QString &key);
    void initModel(QAbstractItemModel *model);
    QStandardItemModel *standardItemModel;

public slots:
    void filterRegExpChanged();

private:
    Ui::TestDialog *ui;

    QSortFilterProxyModel *proxyModel;
};

#endif // TESTDIALOG_H
