#include "advancesettingpage.h"

AdvanceSettingPage::AdvanceSettingPage(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);

//    QHBoxLayout *layout1 = new QHBoxLayout();
//    QLabel *tabLabel = new QLabel("制表符的宽度：");
//    QLineEdit *tabLineEdit = new QLineEdit();
//    tabLineEdit->setMaximumWidth(200);
//    tabLineEdit->setAlignment(Qt::AlignLeft);
//    tabLineEdit->setPlaceholderText("比如：4");


//    layout1->addWidget(tabLabel);
//    layout1->addWidget(tabLineEdit);
//    layout1->addSpacing(20);
//    layout1->addStretch();


//    layout->addLayout(layout1, 0, 0);
//    layout->setContentsMargins(0, 0, 0, 0);
    QLabel *tabLabel = new QLabel("制表符的宽度：");
    QLineEdit *tabLineEdit = new QLineEdit();
    tabLineEdit->setMaximumWidth(200);

    QLabel *tabLabel1 = new QLabel("制表符的宽度：");
    QLineEdit *tabLineEdit1 = new QLineEdit();
    tabLineEdit1->setMaximumWidth(200);

    QLabel *tabLabel2 = new QLabel("制表符的宽度：");
    QLineEdit *tabLineEdit2 = new QLineEdit();
    tabLineEdit2->setMaximumWidth(200);


    QLabel *tabLabel3 = new QLabel("制表符的宽度：");
    QLineEdit *tabLineEdit3 = new QLineEdit();
    tabLineEdit3->setMaximumWidth(200);

    QLabel *tabLabel4 = new QLabel("制表符的宽度：");
    QLineEdit *tabLineEdit4 = new QLineEdit();
    tabLineEdit4->setMaximumWidth(200);

    layout->addWidget(tabLabel, 0, 0);
    layout->addWidget(tabLineEdit, 0, 1);

    layout->addWidget(tabLabel1, 1, 0);
    layout->addWidget(tabLineEdit1, 1, 1);

    layout->addWidget(tabLabel2, 2, 0);
    layout->addWidget(tabLineEdit2, 2, 1);

    layout->addWidget(tabLabel3, 3, 0);
    layout->addWidget(tabLineEdit3, 3, 1);

    layout->addWidget(tabLabel4, 4, 0);
    layout->addWidget(tabLineEdit4, 4, 1);

    layout->setSpacing(15);
    layout->setMargin(10);
}

AdvanceSettingPage::~AdvanceSettingPage()
{

}


