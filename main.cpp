#include <time.h>
#include <QTime>
#include <qdir.h>
#include <qlabel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qmovie.h>
#include <windows.h>
#include <QApplication>
#include "bank.h"
#include "dialog.h"
#include "mainwindow.h"

char ch,vipid[20];
tongji sta[8];//����ÿ������ͳ�ƽ��
time_t cstart,start[8],end[8],rest[8],rstart[8];//end[8]����ÿ���ͻ�����ʱ��
int MaxSeqLen=0,MinSec=0,MaxSec=0,MinRestSec=0,MaxRestSec=0,VIPSERVLen=0;
int vis[]={1,0,1,1,1,0,0,0}; //���浱ǰ����"�ϰ�"�򡰹رա�״̬����Ϣ��״̬
int cur[]={-1,-1,-1,-1,-1,-1,-1,-1};//���浱ǰ���ڷ���ͻ����
int printselect[2];//���浱ǰ�������vip�ͻ�������ͨ�ͻ�
int maxnumber=-1,counts=0,vmaxnumber=-1,vcounts=0,current=-1,vcurrent=-1,iswait=0,isclose=0,flag=1,tactic=0,iswork=0;

int main(int argc, char **argv)
{
    srand((int)time(NULL));
    memset(sta,0,sizeof(sta));
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./image/bank.ico"));
    QMovie *movie;
    movie = new QMovie(":/image/start.gif");//������������
    QLabel *label=new QLabel ("", 0);
    label->setGeometry( 450, 150, 400, 300 );
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->setMovie(movie);
    label->setScaledContents(true);
    movie->start();
    label->show();
    QTime t;
    t.start();
    while(t.elapsed()<5000)
    {
        QApplication::processEvents();
    }
    label->close();
    Dialog login;//���õ�½����
    login.setWindowFlags(Qt::FramelessWindowHint);
    login.show();
    if(login.exec()==QDialog::Accepted){
        MainWindow w;//����������
        w.setWindowTitle(QString::fromLocal8Bit("ģ������ϵͳ"));
        w.show();
        return a.exec();
    }
    else if(login.exec()==QDialog::Rejected) exit(0);
    return a.exec();
}

