#ifndef DIALOGLOWPASS_H
#define DIALOGLOWPASS_H

#include <QDialog>

namespace Ui {
class DialogLowpass;
}

class DialogLowpass : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLowpass(QWidget *parent = 0);
    ~DialogLowpass();

private:
    Ui::DialogLowpass *ui;
public slots:
    void accept();
signals:
    void confirmed(int);
};

#endif // DIALOGLOWPASS_H
