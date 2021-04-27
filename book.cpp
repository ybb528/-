#include "book.h"
#include "ui_book.h"
#include<QPainter>
#include"bookop.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlDriver>
#include<QStringList>
#include<QTableWidgetItem>
book::book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::book)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    QStringList headers;
    headers<<"书名"<<"作者"<<"数量"<<"ISBN号"<<"出版社";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->comboBox->addItem("显示所有图书");
    ui->comboBox->addItem("按书名查询");
    ui->comboBox->addItem("按作者查询");
    ui->comboBox->addItem("ISBN查询");
    ui->comboBox->addItem("按出版社查询");
    connect(ui->opBTN,&QPushButton::clicked,this,[=](){
        bookOp * mybookOp=new bookOp;
        mybookOp->show();
    });
    connect(ui->searchBTN,&QPushButton::clicked,[=](){
        for(int i=ui->tableWidget->rowCount();i>=0;--i)
        {
            ui->tableWidget->removeRow(i);
        }
        this->op();
    });
}
void book::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/pic/pic/bak.jpg");
    painter.drawPixmap(0,0,pix);
}
int book::op()
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
    int tag=mylist.indexOf("BOOK");
    QSqlQuery myquery;
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
        QString str=ui->lineEdit->text();
        int flag=ui->comboBox->currentIndex();
         QString query_str;
         QString str1;
         QString str2;
         QString str3;
         QString str4;
         QString str5;
         int rowcount=0;
        switch (flag) {
        case 0://显示所有图书
            myquery.exec("select * from BOOK");
            while(myquery.next())
            {
                rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                str1=myquery.value(1).toString();
                str2=myquery.value(2).toString();
                str3=myquery.value(3).toString();
                str4=myquery.value(4).toString();
                str5=myquery.value(5).toString();
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(str1));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(str2));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(str3));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(str4));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(str5));
                ui->tableWidget->resizeColumnsToContents();
            }
            break;
        case 1://书名查询
            query_str="select * from BOOK where bookname=";
            query_str.append("'");
            query_str.append(str);
            query_str.append("'");
            //qDebug()<<query_str;
            myquery.exec(query_str);
            while(myquery.next())
            {
                rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                str1=myquery.value(1).toString();
                str2=myquery.value(2).toString();
                str3=myquery.value(3).toString();
                str4=myquery.value(4).toString();
                str5=myquery.value(5).toString();
                qDebug()<<str1<<str2;
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(str1));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(str2));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(str3));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(str4));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(str5));
                ui->tableWidget->resizeColumnsToContents();
            }
            break;
        case 2://作者查询
            query_str="select * from BOOK where writername=";
            query_str.append("'");
            query_str.append(str);
            query_str.append("'");
            qDebug()<<query_str;
            myquery.exec(query_str);
            while(myquery.next())
            {
                rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                str1=myquery.value(1).toString();
                str2=myquery.value(2).toString();
                str3=myquery.value(3).toString();
                str4=myquery.value(4).toString();
                str5=myquery.value(5).toString();
                qDebug()<<str1<<str2;
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(str1));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(str2));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(str3));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(str4));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(str5));
                ui->tableWidget->resizeColumnsToContents();
            }
            break;
        case 3://ISBN
            query_str="select * from BOOK where ISBN=";
            query_str.append("'");
            query_str.append(str);
            query_str.append("'");
            qDebug()<<query_str;
            myquery.exec(query_str);
            while(myquery.next())
            {
                rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                str1=myquery.value(1).toString();
                str2=myquery.value(2).toString();
                str3=myquery.value(3).toString();
                str4=myquery.value(4).toString();
                str5=myquery.value(5).toString();
                qDebug()<<str1<<str2;
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(str1));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(str2));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(str3));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(str4));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(str5));
                ui->tableWidget->resizeColumnsToContents();
            }
            break;
        case 4://出版社
            query_str="select * from BOOK where publishhouse=";
            query_str.append("'");
            query_str.append(str);
            query_str.append("'");
            qDebug()<<query_str;
            myquery.exec(query_str);
            while(myquery.next())
            {
                rowcount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowcount);
                str1=myquery.value(1).toString();
                str2=myquery.value(2).toString();
                str3=myquery.value(3).toString();
                str4=myquery.value(4).toString();
                str5=myquery.value(5).toString();
                qDebug()<<str1<<str2;
                ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(str1));
                ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(str2));
                ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(str3));
                ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(str4));
                ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(str5));
                ui->tableWidget->resizeColumnsToContents();
            }
            break;
        }
    }
    return 0;
}
book::~book()
{
    delete ui;
}
