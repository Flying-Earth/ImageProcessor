#ifndef DIALOGERODE_H
#define DIALOGERODE_H

#include <QDialog>

namespace Ui {
class DialogErode;
}

class DialogErode : public QDialog
{
    Q_OBJECT

public:
    explicit DialogErode(QWidget *parent = 0);
    ~DialogErode();

private:
    Ui::DialogErode *ui;
public slots:
    void accept();
signals:
    void confirmed(int);
};

#endif // DIALOGERODE_H
