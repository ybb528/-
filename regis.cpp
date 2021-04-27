#include "regis.h"
#include "ui_regis.h"
#include<QPainter>
#include<QSqlDatabase>
#include<QSqlDriver>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QStringList>
regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
         if(creatAndOp())
             this->close();
    });
}
void regis::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/pic/pic/login.jpg");
    painter.drawPixmap(0,0,pix);
}
int regis::creatAndOp()
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
     QSqlQuery myquery;
     QStringList mylist=db.tables();
     //for (int i = 0; i < mylist.size(); ++i)
     //           qDebug() << mylist.at(i).toLocal8Bit().constData() << Qt::endl;
     int flagp=mylist.indexOf("USER");
     //qDebug()<<flagp;
     if(flagp==-1)//未找到用户表（储存密码）,建表
     {
         bool flag=myquery.exec("create table USER(id int primary key, name text, password text)");
         if(flag==false)
      {
             QMessageBox::critical(0,"FAIL TO CTEAT TABLE",myquery.lastError().text());
               db.close();
             return 0;
      }

     }
     //QString clear_sql = "delete from student";
     //myquery.prepare(clear_sql);
     QString user_name=ui->name->text();
     QString password1=ui->password1->text();
     QString password2=ui->password2->text();
     int tag=QString::compare(password1,password2);
     if(tag==0)
     {
         QString select_max_sql = "select max(id) from USER";
         int max_id = 0;
         myquery.prepare(select_max_sql);
         if(!myquery.exec())
         {
             qDebug() << myquery.lastError()<<"this is for test";
         }
         else
         {
                  myquery.next();//需要特别注意，刚执行完query.exec("select *from student")query是指向结果集以外的
                  max_id = myquery.value(0).toInt();
                  qDebug() << QString("max id:%1").arg(max_id);
         }
         myquery.exec("select * from USER");
         int flag_for_name=1;
         while(myquery.next())
         {
             QString query_name=myquery.value(1).toString();
             if(QString::compare(user_name,query_name)==0)
                {
                 flag_for_name=0;
                 QMessageBox::critical(0,"error","用户名已存在");
                 break;
             }
         }
         if(flag_for_name==1)
         {
             myquery.prepare("INSERT INTO USER(id,name,password)"
                         "VALUES (:id, :name, :password)");
                 max_id=max_id+1;
               myquery.bindValue(0,max_id);
               myquery.bindValue(1,user_name);
               myquery.bindValue(2,password1);
              bool flag=myquery.exec();
         if(flag==true)
      {
             QMessageBox::information(0,"SUCCESS","注册成功");
               db.close();
             return 1;
      }
         else
         {
             QMessageBox::critical(0,"error",myquery.lastError().text());
         }
         }
     }
     else
     {
         QMessageBox::critical(0,"error","两次密码输入不一致");
     }
       db.close();
     return 0;
}
regis::~regis()
{
    delete ui;
}
