#ifndef DIALOGGAUSS_H
#define DIALOGGAUSS_H

#include <QDialog>

namespace Ui {
class DialogGauss;
}

class DialogGauss : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGauss(QWidget *parent = 0);
    ~DialogGauss();

private:
    Ui::DialogGauss *ui;
public slots:
    void accept();
signals:
    void confirmed(int,double);
};

#endif // DIALOGGAUSS_H
