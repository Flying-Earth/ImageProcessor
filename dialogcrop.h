#ifndef DIALOGCROP_H
#define DIALOGCROP_H

#include <QDialog>

namespace Ui {
class DialogCrop;
}

class DialogCrop : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCrop(QWidget *parent = 0);
    ~DialogCrop();

private:
    Ui::DialogCrop *ui;

public slots:
    void accept();
signals:
    void confirmed(double,double);
};

#endif // DIALOGCROP_H
