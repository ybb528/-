#include "bookop.h"
#include "ui_bookop.h"
#include<QPainter>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlDriver>
#include<QStringList>
bookOp::bookOp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookOp)
{
    ui->setupUi(this);
    connect(ui->clearBtn,&QPushButton::clicked,[=](){
       ui->bookName->clear();
       ui->bookCount->clear();
       ui->ISBNnumber->clear();
       ui->writerName->clear();
       ui->publishHouse->clear();
    });
    connect(ui->insertBTN,&QPushButton::clicked,[=](){
       insert_data();
    });
    connect(ui->changeBTN,&QPushButton::clicked,[=](){
       change_data();
    });
    connect(ui->delBTN,&QPushButton::clicked,[=](){
       del_data();
    });
}
void bookOp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/pic/pic/back5.jpg");
    painter.drawPixmap(0,0,pix);
}
bookOp::~bookOp()
{
    delete ui;
}
int bookOp::del_data(){
    //ISBN是必填项
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
    QSqlQuery myquery;
    int tag=mylist.indexOf("BOOK");
    if(tag==-1)
    {
        bool flag=myquery.exec("create table BOOK(id int primary key,"
                               " bookname text, "
                               "writername text,"
                               "bookcount text,"
                               "ISBN text,"
                               "publishhouse text)");
        if(flag==false)
                QMessageBox::critical(0,"BIGerror",myquery.lastError().text());
    }
    else
    {
        QString ISBN=ui->ISBNnumber->text();
        QString bookname=ui->bookName->text();
        if(ISBN!=NULL)
        {
            QString str="delete from BOOK where ISBN=";
            str.append("'");
            str.append(ISBN);
            str.append("'");
            if(!myquery.exec(str))
                QMessageBox::critical(0,"DEl ERROR",myquery.lastError().text());
            else
                QMessageBox::information(0,"SUCCESS","删除成功");
        }
        else if(bookname!=NULL)
        {
            QString str="delete from BOOK where bookname=";
            str.append("'");
            str.append(bookname);
            str.append("'");
            if(!myquery.exec(str))
                QMessageBox::critical(0,"DEl ERROR",myquery.lastError().text());
            else
                QMessageBox::information(0,"SUCCESS","删除成功");
        }
        else
        {
            QMessageBox::critical(0,"DEL ERROR","书名和ISBN不能全为空");
        }
    }
    return 0;
}
int bookOp::change_data()
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
    QSqlQuery myquery;
    int tag=mylist.indexOf("BOOK");
    if(tag==-1)
    {
        bool flag=myquery.exec("create table BOOK(id int primary key,"
                               " bookname text, "
                               "writername text,"
                               "bookcount text,"
                               "ISBN text,"
                               "publishhouse text)");
        if(flag==false)
                QMessageBox::critical(0,"BIGerror",myquery.lastError().text());
    }
    else
    {
        int queryid=0;
        QString bookname=ui->bookName->text();
        QString writername=ui->writerName->text();
        QString bookcount=ui->bookCount->text();
        QString ISBN=ui->ISBNnumber->text();
        QString publishhouse=ui->publishHouse->text();
        //***
        if(bookname!=NULL)//按书名号查找更新
        {
            myquery.clear();
            QString str="select * from BOOK where bookname=";
            str.append("'");
            str.append(bookname);
            str.append("'");
            myquery.exec(str);
            if(myquery.first()==false)
              {
                QMessageBox::critical(0,"UPDATE ERROR","未找到该书");
                return 0;
            }
            myquery.first();
            queryid=myquery.value(0).toInt();
            if(writername==NULL)
            writername=myquery.value(2).toString();
            if(bookcount==NULL)
             bookcount=myquery.value(3).toString();
            if(ISBN==NULL)
                ISBN=myquery.value(4).toString();
            if(publishhouse==NULL)
                publishhouse=myquery.value(5).toString();
            QString str1="delete from BOOK where bookname=";
            str1.append("'");
            str1.append(bookname);
            str1.append("'");
            myquery.exec(str1);
            myquery.prepare("replace into BOOK(id,bookname,writername,bookcount,ISBN,publishhouse)"
                        "VALUES (?,?,?,?,?,?)");
              myquery.addBindValue(queryid);
             myquery.addBindValue(bookname);
              myquery.addBindValue(writername);
            myquery.addBindValue(bookcount);
            myquery.addBindValue(ISBN);
           myquery.addBindValue(publishhouse);
             bool flagp=myquery.exec();
            if(flagp==true)
         {
                QMessageBox::information(0,"SUCCESS","更新成功");
                return 1;
         }
            else
            {
                QMessageBox::critical(0,"insert error",myquery.lastError().text());
            }
            qDebug()<<"this is for test";
        }
        else
        {
            QMessageBox::critical(0,"UPDATE ERROR","书名不能为空");
        }
    }
    return 0;
}
int bookOp::insert_data()
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
  //  for (int i = 0; i < mylist.size(); ++i)
    //       qDebug() << mylist.at(i).toLocal8Bit().constData() << Qt::endl;
    int tag=mylist.indexOf("BOOK");
    QSqlQuery myquery;
    QString bookname=ui->bookName->text();
    QString writername=ui->writerName->text();
    QString bookcount=ui->bookCount->text();
    QString ISBN=ui->ISBNnumber->text();
    QString publishhouse=ui->publishHouse->text();
    /*
       QString strTableNmae = "BOOK";
       QString str = "PRAGMA table_info(" + strTableNmae + ")";

       myquery.prepare(str);
       if (myquery.exec())
       {
           while (myquery.next())
           {
               qDebug() << QString(QString::fromLocal8Bit("字段数:%1     字段名:%2     字段类型:%3")).arg(myquery.value(0).toString()).arg(myquery.value(1).toString()).arg(myquery.value(2).toString());
           }
       }
       else
       {
           qDebug() <<myquery.lastError();
       }
    */
    int max_id = 0;
    if(tag==-1)//建表
    {
        //, writername text,bookcount text,ISBN text,publishhouse text
        bool flag=myquery.exec("create table BOOK(id int primary key,"
                               " bookname text, "
                               "writername text,"
                               "bookcount text,"
                               "ISBN text,"
                               "publishhouse text)");
        if(flag==false)
                QMessageBox::critical(0,"BIGerror",myquery.lastError().text());
    }
    else
        {
                QString select_max_sql = "select max(id) from BOOK";
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
                //,writername,bookcount,ISBN,publishhouse
                //,: writername,: bookcount,: ISBN,: publishhouse
                myquery.clear();
                myquery.prepare("insert into BOOK(id,bookname,writername,bookcount,ISBN,publishhouse)"
                            "VALUES (?,?,?,?,?,?)");
                    max_id=max_id+1;
                  myquery.addBindValue(max_id);
                 myquery.addBindValue(bookname);
                  myquery.addBindValue(writername);
                myquery.addBindValue(bookcount);
                myquery.addBindValue(ISBN);
               myquery.addBindValue(publishhouse);
                 bool flagp=myquery.exec();
                if(flagp==true)
             {
                    QMessageBox::information(0,"SUCCESS","插入成功");
                      db.close();
                    return 1;
             }
                else
                {
                    QMessageBox::critical(0,"insert error",myquery.lastError().text());
                }
    }
     db.close();
     return 0;
}
