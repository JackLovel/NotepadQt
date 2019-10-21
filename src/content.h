#ifndef CONTENT_H
#define CONTENT_H

#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QBoxLayout>

//#include "baseinfo.h"
#include "contact.h"
//#include "detail.h"

class Content : public QFrame
{
public:
    Content(QWidget *parent = nullptr);
    ~Content();

    QStackedWidget *stack;
    QPushButton *AmendBtn;
    QPushButton *CloseBtn;

//    BaseInfo *baseInfo;
    Contact *contact;
//    Detail *detail;

};

#endif // CONTENT_H
