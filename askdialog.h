#ifndef ASKDIALOG_H
#define ASKDIALOG_H
#include <QDialog>
#include<QPainter>
namespace Ui {
class AskDialog;
}

class AskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AskDialog(QWidget *parent = nullptr);
    ~AskDialog();
    void paintEvent(QPaintEvent*);
private:
    Ui::AskDialog *ui;
};

#endif // ASKDIALOG_H
