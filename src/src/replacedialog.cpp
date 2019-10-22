#include "replacedialog.h"
#include <QGridLayout>

ReplaceDialog::ReplaceDialog(QWidget *parent) : QDialog(parent)
{
    findLabel = new QLabel(tr("查找内容"));
    replaceLabel = new QLabel(tr("替换为"));
    findLineEdit = new QLineEdit();
    replaceLineEdit = new QLineEdit();
    findNextButton = new QPushButton(tr("查找下一个"));
    replacedOneButton = new QPushButton(tr("替换"));
    replacedAllButton = new QPushButton(tr("全部替换"));
    cancelButton = new QPushButton(tr("取消"));
    ignoreFlag = new QCheckBox(tr("区分大小写"));

    QGridLayout *mainLayout = new QGridLayout(this);
    QVBoxLayout *vboxly = new QVBoxLayout();

    vboxly->addWidget(replacedAllButton);
    vboxly->addWidget(cancelButton);
    mainLayout->addWidget(findLabel, 0, 0);
    mainLayout->addWidget(findLineEdit, 0, 1);
    mainLayout->addWidget(findNextButton, 0, 2);
    mainLayout->addWidget(replaceLabel, 1, 0);
    mainLayout->addWidget(replaceLineEdit, 1, 1);
    mainLayout->addWidget(replacedOneButton, 1, 2);

    mainLayout->addWidget(ignoreFlag, 2, 1);
    mainLayout->addLayout(vboxly, 2, 2);


    //  init
    findLineEdit->setText(tr(""));
    replaceLineEdit->setText(tr(""));
    findNextButton->setEnabled(false);
    replacedOneButton->setEnabled(false);
    replacedAllButton->setEnabled(false);
    setMaximumSize(300, 100);
    setWindowTitle(tr("替换"));

    connect(findLineEdit, &QLineEdit::textChanged, this, &ReplaceDialog::chooseStrSlot);
    connect(cancelButton, &QPushButton::clicked, this, [=]() {
        this->close();
    });
    connect(findNextButton, &QPushButton::clicked, this, &ReplaceDialog::findButtonStateSlot);

    connect(replacedOneButton, &QPushButton::clicked, this, &ReplaceDialog::replaceOneButtonStateSlot);
    connect(replacedAllButton, &QPushButton::clicked, this, &ReplaceDialog::replaceAllButtonStateSlot);
}

ReplaceDialog::~ReplaceDialog()
{

}

void ReplaceDialog::chooseStrSlot()
{
    if (!findLineEdit->text().isEmpty()) {
        findNextButton->setEnabled(true);
        replacedOneButton->setEnabled(true);
        replacedAllButton->setEnabled(true);
    } else {
        findNextButton->setEnabled(false);
        replacedOneButton->setEnabled(false);
        replacedAllButton->setEnabled(false);
    }
}

void ReplaceDialog::findButtonStateSlot()
{
    if (ignoreFlag->isChecked()) {
        emit findReplaceStr(findLineEdit->text(), true);
    } else {
        emit findReplaceStr(findLineEdit->text(), false);
    }
}

void ReplaceDialog::replaceOneButtonStateSlot()
{
    emit replaceCurOneStr(findLineEdit->text(), replaceLineEdit->text());
}

void ReplaceDialog::replaceAllButtonStateSlot()
{
    if (ignoreFlag->isChecked()) {
        emit replaceAllStr(findLineEdit->text(), replaceLineEdit->text(), true);
    } else {
        emit replaceAllStr(findLineEdit->text(), replaceLineEdit->text(), false);
    }
}










