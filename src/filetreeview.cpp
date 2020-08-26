#include "filetreeview.h"
#include <QTextCodec>

FileTreeVIew::FileTreeVIew()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    model = new QStandardItemModel(4, 2);

}

void FileTreeVIew::mouseDoubleClickEvent(QMouseEvent *event)
{

}
