#include "askdialog.h"
#include "ui_askdialog.h"
#include"regis.h"
#include"login.h"
AskDialog::AskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskDialog)
{
    ui->setupUi(this);
    connect(ui->RegisterButton,&QPushButton::clicked,this,[=](){
        regis* reg=new regis;
        reg->show();
    });
    connect(ui->LoginButton,&QPushButton::clicked,this,[=](){
        login* log=new login;
        log->show();
    });
}
void AskDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/pic/pic/ask.png");
    painter.drawPixmap(0,0,pix);
}
AskDialog::~AskDialog()
{
    delete ui;
}
