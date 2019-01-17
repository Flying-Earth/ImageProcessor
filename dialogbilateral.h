#ifndef DIALOGBILATERAL_H
#define DIALOGBILATERAL_H

#include <QDialog>

namespace Ui {
class DialogBilateral;
}

class DialogBilateral : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBilateral(QWidget *parent = 0);
    ~DialogBilateral();

private:
    Ui::DialogBilateral *ui;
public slots:
    void accept();
signals:
    void confirmed(int,double,double);
};

#endif // DIALOGBILATERAL_H
