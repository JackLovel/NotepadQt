#ifndef ADVANCESETTINGPAGE_H
#define ADVANCESETTINGPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class AdvanceSettingPage : public QWidget
{
    Q_OBJECT

public:
    AdvanceSettingPage(QWidget *parent = nullptr);
    ~AdvanceSettingPage();

private:
    QGridLayout *layout;
    QLabel *tabLabel;
    QLineEdit *tabLineEdit;
};

#endif // ADVANCESETTINGPAGE_H
