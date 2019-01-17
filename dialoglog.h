#ifndef DIALOGLOG_H
#define DIALOGLOG_H

#include <QDialog>

namespace Ui {
class DialogLog;
}

class DialogLog : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLog(QWidget *parent = 0);
    ~DialogLog();

private:
    Ui::DialogLog *ui;
public slots:
    void accept();

signals:
    void confirmed(double);
};

#endif // DIALOGLOG_H
