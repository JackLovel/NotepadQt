#include "md5dialog.h"

#include <QFileDialog>
#include <QDebug>

Md5Dialog::Md5Dialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("字符生成MD5");
    resize(500, 200);

   inputLabel = new QLabel("字符：");
   inputLineEdit = new QLineEdit();
   resultLabel = new QLabel("结果：");
   resultLineEdit = new QLineEdit();
   resultLineEdit->setReadOnly(true);
   QSizePolicy sizePolicy = resultLineEdit->sizePolicy();
   sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
   resultLineEdit->setSizePolicy(sizePolicy);

   copyButton = new QPushButton(tr("复制到剪贴板"));
   QPushButton *fileMd5Button = new QPushButton(tr("从文件中生成"));

   QGridLayout *layout = new QGridLayout(this);
   layout->addWidget(inputLabel, 0, 0);
   layout->addWidget(inputLineEdit, 0, 1);
   layout->addWidget(resultLabel, 1, 0);
   layout->addWidget(resultLineEdit, 1, 1);
   layout->addWidget(copyButton, 2, 0);

   layout->addWidget(fileMd5Button, 2, 1);
   connect(fileMd5Button, &QPushButton::clicked, this, &Md5Dialog::getMd5FileSlot);

   connect(inputLineEdit, &QLineEdit::textChanged, this, &Md5Dialog::getMd5StringSlot);
   connect(copyButton, &QPushButton::clicked, this, &Md5Dialog::clipboardSlot);
}

Md5Dialog::~Md5Dialog()
{

}

void Md5Dialog::getMd5StringSlot()
{
    QString inputText = inputLineEdit->text();
    if (!inputText.isEmpty()) {
        QByteArray byteText = inputText.toUtf8();
        QString strPwdMd5 = QCryptographicHash::hash(byteText, QCryptographicHash::Md5).toHex();
        resultLineEdit->setText(strPwdMd5);
        return;
    }

    resultLineEdit->clear();
    return;
}

void Md5Dialog::clipboardSlot()
{
    QClipboard *clipBoard = QApplication::clipboard();
    QString resultText = resultLineEdit->text();
    if (!resultText.isEmpty()) {
        clipBoard->setText(resultText);
        return;
    }

    return;
}

void Md5Dialog::getMd5FileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    const qint32 bufferSize = 1024;
    char buffer[bufferSize];
    int bytesRead;

    qint32 fileSize = file.size();
    int readSize = qMin(fileSize, bufferSize);

    QCryptographicHash hash(QCryptographicHash::Md5);
    while (readSize > 0 && (bytesRead = file.read(buffer, readSize)) > 0) {
        fileSize -= bytesRead;
        hash.addData(buffer, bytesRead);
        readSize = qMin(fileSize, bufferSize);
    }

    file.close();
    QString md5Value = hash.result().toHex();
    qDebug() << md5Value;

    return;
}
