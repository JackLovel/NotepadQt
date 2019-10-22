#include "golinedialog.h"

GoLineDialog::GoLineDialog(QWidget *parent) : QDialog(parent)
{
    setFixedSize(400, 150);
    setWindowTitle("跳转");

    okButton = new QPushButton("确定");
    okButton->setFixedSize(70, 70);

    label = new QLabel();
    label->setText("跳转行");

    lineEdit = new QLineEdit();

    layout = new QHBoxLayout(this);

    layout->addStretch();
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(okButton);
    layout->addStretch();

    connect(okButton, &QPushButton::clicked, this, &GoLineDialog::okAction);
    setLayout(layout);
}

GoLineDialog::~GoLineDialog()
{

}

void GoLineDialog::okAction()
{
    QString lineNumber = lineEdit->text();
    if (!lineNumber.isEmpty()) {
        emit sendLineNumber(lineNumber.toInt());
    }
}
