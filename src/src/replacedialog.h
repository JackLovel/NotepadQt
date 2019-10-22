#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();

signals:
    void replaceAllStr(QString, QString, bool);
    void replaceCurOneStr(QString, QString);
    void findReplaceStr(QString, bool);

private slots:
    void chooseStrSlot();
    void findButtonStateSlot();
    void replaceOneButtonStateSlot();
    void replaceAllButtonStateSlot();

private:
//    QLineEdit *find_str;
    QLineEdit *findLineEdit;
//    QLineEdit *replace_str;
    QLineEdit *replaceLineEdit;
    QPushButton *findNextButton;
    QPushButton *replacedOneButton;
    QPushButton *replacedAllButton;
    QPushButton *cancelButton;
    QCheckBox *ignoreFlag;
    QLabel *findLabel;
    QLabel *replaceLabel;
};

#endif // REPLACEDIALOG_H
