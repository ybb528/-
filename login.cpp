#include "login.h"
#include "ui_login.h"
#include<QPainter>
#include<QMessageBox>
#include<QSqlError>
#include<QStringList>
#include<QString>
#include"book.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,[=]()
    {
        int flag=connectAndOp();
        if(flag==1)
        {
           book* mybook=new book;
           mybook->show();
            this->close();
        }
    });
}
void login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/pic/pic/login.jpg");
    painter.drawPixmap(0,0,pix);
}
int login::connectAndOp()
{
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db= QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/scooters.dat");    //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
    }
     if (!db.open()) {
            QMessageBox::warning(0, QObject::tr("Database Error"),db.lastError().text());
              db.close();
            return 0;
     }
     QStringList mylist=db.tables();
     int tag=mylist.indexOf("USER");
     QSqlQuery myquery;
     if(tag==-1)//未找到用户表（储存密码）,建表
     {
         bool flag=myquery.exec("create table USER(id int primary key, name text, password text)");
         if(flag==false)
      {
             QMessageBox::critical(0,"FAIL TO CTEAT TABLE",myquery.lastError().text());
               db.close();
             return 0;
      }

     }
     else//找到用户表，进行查询
     {
         QString user_name=ui->userName->text();
         QString password=ui->passWord->text();
         myquery.exec("select * from USER");
         QString name_query;
         QString password_query;
         int flag_name=0;
         while(myquery.next())
         {
             name_query=myquery.value(1).toString();
             password_query=myquery.value(2).toString();
             if(QString::compare(name_query,user_name)==0)
              {
                 flag_name=1;
                 break;
             }
         }
         if(flag_name==0)
         {QMessageBox::information(0,"error","用户名不存在");
               db.close();
         return 0;}
         int t=QString::compare(password,password_query);
         if(t==0)
      {
               db.close();
             return 1;

     }
         else
         {
              QMessageBox::critical(0,"ERROR","密码错误，请重新输入密码");
                db.close();
              return 0;
         }

     }
     db.close();
     return 0;
}
login::~login()
{
    delete ui;
}
