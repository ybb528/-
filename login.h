#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QSqlDatabase>
#include<QSqlDriver>
#include<QSqlQuery>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void paintEvent(QPaintEvent*);
    int connectAndOp();//连接数据库并进行操作
private:
    Ui::login *ui;
};

#endif // LOGIN_H
