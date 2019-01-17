#ifndef DIALOGMID_H
#define DIALOGMID_H

#include <QDialog>

namespace Ui {
class DialogMid;
}

class DialogMid : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMid(QWidget *parent = 0);
    ~DialogMid();

private:
    Ui::DialogMid *ui;
public slots:
    void accept();
signals:
    void confirmed(int);

};

#endif // DIALOGMID_H
