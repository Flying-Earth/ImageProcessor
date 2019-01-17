#ifndef DIALOGDILATE_H
#define DIALOGDILATE_H

#include <QDialog>

namespace Ui {
class DialogDilate;
}

class DialogDilate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDilate(QWidget *parent = 0);
    ~DialogDilate();

private:
    Ui::DialogDilate *ui;
public slots:
    void accept();
signals:
    void confirmed(int);
};

#endif // DIALOGDILATE_H
