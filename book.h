#ifndef BOOK_H
#define BOOK_H

#include <QWidget>

namespace Ui {
class book;
}

class book : public QWidget
{
    Q_OBJECT

public:
    explicit book(QWidget *parent = nullptr);
    ~book();
     void paintEvent(QPaintEvent*);
    int op();
private:
    Ui::book *ui;
};

#endif // BOOK_H
