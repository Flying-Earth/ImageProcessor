#ifndef DIALOGHIGHPASS_H
#define DIALOGHIGHPASS_H

#include <QDialog>

namespace Ui {
class DialogHighpass;
}

class DialogHighpass : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHighpass(QWidget *parent = 0);
    ~DialogHighpass();

private:
    Ui::DialogHighpass *ui;
public slots:
    void accept();
signals:
    void confirmed(int);
};

#endif // DIALOGHIGHPASS_H
