#ifndef BOOKOP_H
#define BOOKOP_H

#include <QDialog>

namespace Ui {
class bookOp;
}

class bookOp : public QDialog
{
    Q_OBJECT

public:
    explicit bookOp(QWidget *parent = nullptr);
    ~bookOp();
void paintEvent(QPaintEvent*);
int insert_data();
int change_data();
int del_data();
private:
    Ui::bookOp *ui;
};

#endif // BOOKOP_H
