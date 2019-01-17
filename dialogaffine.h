#ifndef DIALOGAFFINE_H
#define DIALOGAFFINE_H

#include <QDialog>
#include <matrix.h>

namespace Ui {
class DialogAffine;
}

class DialogAffine : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAffine(QWidget *parent = 0);
    ~DialogAffine();

private:
    Ui::DialogAffine *ui;
public slots:
    void accept();
signals:
    void confirmed(const Matrix<double> &);
};

#endif // DIALOGAFFINE_H
