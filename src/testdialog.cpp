#include "testdialog.h"
#include "ui_testdialog.h"

#include <QStandardItem>

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    proxyModel = new QSortFilterProxyModel;
    standardItemModel = new QStandardItemModel(0, 1, this);

    ui->lineEdit->setPlaceholderText("输入...");

    ui->sourceView->setRootIsDecorated(false);
    ui->sourceView->setAlternatingRowColors(true);

    ui->treeView->setRootIsDecorated(false);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setModel(proxyModel);
    ui->treeView->setSortingEnabled(true);

    connect(ui->lineEdit, &QLineEdit::textChanged,
              this, &TestDialog::filterRegExpChanged);

    initModel(standardItemModel);

    setSourceModel(standardItemModel);

    setWindowTitle("测试对话框");
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::setSourceModel(QAbstractItemModel *model)
{
    proxyModel->setSourceModel(model);
    ui->sourceView->setModel(model);
}

void TestDialog::filterRegExpChanged() {
    QRegExp::PatternSyntax syntax = QRegExp::FixedString;

    Qt::CaseSensitivity caseSen = Qt::CaseSensitivity(0);
    QString text = ui->lineEdit->text();

    QRegExp regExp(text, caseSen, syntax);
    proxyModel->setFilterRegExp(regExp);
}

void TestDialog::addMail(QAbstractItemModel *model, const QString &name)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), name);
}

void TestDialog::initModel(QAbstractItemModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, "姓名");

    addMail(model, "li hong");
    addMail(model, "wang gang");
}
