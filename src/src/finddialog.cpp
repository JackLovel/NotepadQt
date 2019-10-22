#include "finddialog.h"
#include <QGridLayout>
#include <QGroupBox>

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("查找"));
    findLabel = new QLabel(tr("查找"));
    ignoreLabel = new QLabel(tr("区分大小写"));
    nextLabel = new QLabel(tr("向后"));
    backLabel = new QLabel(tr("向前"));
    findEdit = new QLineEdit;
    findButton = new QPushButton(tr("查找下一个"));
    nextRadio = new QRadioButton;
    backRadio = new QRadioButton;
    ignore_flag = new QCheckBox;

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(findLabel, 0, 0);
    gridLayout->addWidget(findEdit, 0, 1);
    gridLayout->addWidget(findButton, 0, 3);

    QHBoxLayout *ignoreLayout = new QHBoxLayout;
    ignoreLayout->setSpacing(10);
    ignoreLayout->addWidget(ignoreLabel);
    ignoreLayout->addWidget(ignore_flag);

    QHBoxLayout *radioLayout = new QHBoxLayout;
    radioLayout->addWidget(nextLabel);
    radioLayout->addWidget(nextRadio);
    radioLayout->addWidget(backLabel);
    radioLayout->addWidget(backRadio);

    QGroupBox *groupRadio = new QGroupBox(tr("方向"), this);
    groupRadio->setLayout(radioLayout);

    QHBoxLayout *doRadio = new QHBoxLayout;
    doRadio->addWidget(groupRadio);

    gridLayout->addLayout(ignoreLayout, 1, 0);
    gridLayout->addLayout(doRadio, 1, 1);

    setMaximumSize(300, 100);
    nextRadio->setChecked(true);
    findButton->setEnabled(false);

    connect(findEdit, &QLineEdit::textChanged, this, &FindDialog::buttonStateSlot);
    connect(findButton, &QPushButton::clicked, this, &FindDialog::findButtonSlot);
}

FindDialog::~FindDialog()
{

}

void FindDialog::buttonStateSlot()
{
    if (!findEdit->text().isEmpty()) {
        findButton->setEnabled(true);
        return;
    }

    findButton->setEnabled(false);
}

void FindDialog::findButtonSlot()
{
    if (findEdit->text().isEmpty())
        return;

    QString str = findEdit->text();
    if (nextRadio->isChecked()) {
        if (ignore_flag->isChecked()) {
            emit sendQueryText(str, true, true);
        } else {
            emit sendQueryText(str, false, true);
        }
    }

    if (backRadio->isChecked()) {
        if (ignore_flag->isChecked()) {
            emit sendQueryText(str, true, false);
        } else {
            emit sendQueryText(str, false, false);
        }
    }
}








