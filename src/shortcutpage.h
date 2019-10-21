#ifndef SHORTCUTPAGE_H
#define SHORTCUTPAGE_H

#include <QDir>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSettings>

class ShortCutPage : public QWidget
{
    Q_OBJECT
public:
    ShortCutPage(QWidget *parent = nullptr);
    ~ShortCutPage();

    void setup();

signals:

private slots:

private:
    QGridLayout *layout;
    QLabel *newLabel;
    QLineEdit *newLineEdit;
    QLabel *openLabel;
    QLineEdit *openLineEdit;
    QLabel *saveLabel;
    QLineEdit *saveLineEdit;
    QLabel *saveAsLabel;
    QLineEdit *saveAsLineEdit;
    QLabel *printLabel;
    QLineEdit *printLineEdit;
    QLabel *closeLabel;
    QLineEdit *closeLineEdit;
    QLabel *copyLabel;
    QLineEdit *copyLineEdit;
    QLabel *cutLabel;
    QLineEdit *cutLineEdit;
    QLabel *pasteLabel;
    QLineEdit *pasteLineEdit;
    QLabel *undoLabel;
    QLineEdit *undoLineEdit;
    QLabel *redoLabel;
    QLineEdit *redoLineEdit;

    QPushButton *defaultBtn;
    QPushButton *okButton;
    QPushButton *cancelBtn;
};

#endif // SHORTCUTPAGE_H
