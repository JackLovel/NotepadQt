#include "filetreeview.h"
#include <QTextCodec>

FileTreeView::FileTreeView()
{
    this->setVisible(false);

    loadView();
}

FileTreeView::~FileTreeView()
{

}

// load view
void FileTreeView::loadView()
{
    model.setRootPath(path);
    if (!path.isEmpty()) {
        this->setModel(&model);
        const QModelIndex rootIndex = model.index(QDir::cleanPath(path));
        if (rootIndex.isValid()) {
            this->setRootIndex(rootIndex);
        }
    }
}



