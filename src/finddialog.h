#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

signals:
    void sendQueryText(QString, bool, bool);
//    void FindTextDataButtonClickedSignal(QString, bool, bool);

private slots:
    void buttonStateSlot();
    void findButtonSlot();

private:
    QLineEdit *findEdit;
    QLabel *findLabel, *ignoreLabel, *nextLabel, *backLabel;
    QPushButton *findButton;
    QRadioButton *nextRadio;
    QRadioButton *backRadio;
    QCheckBox *ignore_flag;
};

#endif // FINDDIALOG_H












