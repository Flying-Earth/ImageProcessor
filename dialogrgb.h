#ifndef DIALOGRGB_H
#define DIALOGRGB_H

#include <QDialog>

namespace Ui {
class Dialogrgb;
}

class Dialogrgb : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogrgb(QWidget *parent = 0);
    ~Dialogrgb();

private:
    Ui::Dialogrgb *ui;
public slots:
    void accept();
signals:
    void confirmed();
};

#endif // DIALOGRGB_H
