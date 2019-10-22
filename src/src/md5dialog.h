#ifndef MD5DIALOG_H
#define MD5DIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCryptographicHash>
#include <QApplication>
#include <QClipboard>

class Md5Dialog : public QDialog
{
    Q_OBJECT

public:
    Md5Dialog(QWidget *parent = nullptr);
    ~Md5Dialog();

private slots:
    void getMd5StringSlot();
    void clipboardSlot();
    void getMd5FileSlot();

private:
    QLabel *inputLabel;
    QLineEdit *inputLineEdit;
    QLabel *resultLabel;
    QLineEdit *resultLineEdit;
    QPushButton *copyButton;
};

#endif // MD5DIALOG_H
