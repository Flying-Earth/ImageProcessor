#ifndef DIALOGCONTRAST_H
#define DIALOGCONTRAST_H

#include <QDialog>

namespace Ui {
class DialogContrast;
}

class DialogContrast : public QDialog
{
    Q_OBJECT

public:
    explicit DialogContrast(QWidget *parent = 0);
    ~DialogContrast();

private:
    Ui::DialogContrast *ui;
public slots:
    void accept();

signals:
    void confirmed(double,double);
};

#endif // DIALOGCONTRAST_H
