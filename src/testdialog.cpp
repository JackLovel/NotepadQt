#include "testdialog.h"
#include "ui_testdialog.h"

#include <QStandardItem>

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    proxyModel = new QSortFilterProxyModel;
    standardItemModel = new QStandardItemModel(0, 2, this);

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

    // 隐藏源视图
    ui->sourceView->setHidden(true);

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

void TestDialog::addMail(QAbstractItemModel *model, const QString &name, const QString &key)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), name);
    model->setData(model->index(0, 1), key);
}

void TestDialog::initModel(QAbstractItemModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, "名称");
    model->setHeaderData(1, Qt::Horizontal, "快捷键");
    addMail(model, "查找", "ctrl+a");
    addMail(model, "替换", "ctrl+r");
}
