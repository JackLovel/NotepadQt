#ifndef GOLINEDIALOG_H
#define GOLINEDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDialog>

class GoLineDialog : public QDialog
{
    Q_OBJECT

public:
    GoLineDialog(QWidget *parent = nullptr);
    ~GoLineDialog();

signals:
    void sendLineNumber(int xCursor);

private slots:
    void okAction();

private:
    QPushButton *okButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *layout;
};

#endif // GOLINEDIALOG_H
