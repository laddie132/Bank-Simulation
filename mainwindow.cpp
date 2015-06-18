#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <QTime>
#include "bank.h"
#include <time.h>

extern int iswait,isclose,maxnumber,counts,vmaxnumber,vcounts,current,vcurrent,tactic,iswork;
extern time_t rest[8];
extern char vipid[20];
extern  int vis[8],cur[8],printselect[2];
int filetimes=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_5->setAttribute(Qt::WA_TranslucentBackground);
    ui->window->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label_6->setAttribute(Qt::WA_TranslucentBackground);
    ui->window->setColumnWidth(0,90);
    ui->window->setColumnWidth(1,90);
    ui->window->setColumnWidth(2,85);
    ui->window->setColumnWidth(3,85);
    ui->window->setColumnWidth(4,85);
    ui->window->setColumnWidth(5,85);
    ui->window->setColumnWidth(6,85);
    ui->window->setColumnWidth(7,86);
    for(int i=0;i<8;i++)
    {
        ui->window->setRowHeight(i,40);
    }
    vipinform1=new vipinform;
    configw1=new configw;
    configw1->setWindowTitle(QString::fromLocal8Bit("����"));
    configw1->exec();
    timeUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    this->close();
}

void MainWindow::on_action_4_triggered()
{
    QMessageBox::about(this,QString::fromLocal8Bit("����"),
          QString::fromLocal8Bit(" <font color='red'>Virtual Bank System 2.5.0 (opensource)</font>"
                                " <br><br>Based on v 1.1.0 (32 bit)"

                                 "<br><br>Built on June 16 2015 at 21:47:12"

                                " <br><br>�����޶��汾 2.4.0"
                                 "<br><br>��Ŀ��ҳ��https://github.com/laddie132/Virtual-Bank-System-2.0"

                                 " <br><br>���ߣ�L.Laddie�Ŷ�  ��ҳ��http://laddie132.pe.hu/"

                               "  <br><br>Copyright 2015-2015 The Qt Company Ltd. All rights reserved." ));
}

void MainWindow::on_action_2_triggered()
{
    configw1->exec();//�������ļ��е������
}

void MainWindow::on_outbank_clicked()//�����°��ź�
{
    iswait=1;
    QMessageBox::information(this,QString::fromLocal8Bit("�°�"),QString::fromLocal8Bit("���н���ȴ��°�״̬��"),QMessageBox::Yes);
}

void MainWindow::on_pausepush_clicked()//����������ͣ�ź�
{

    bool ok;
    int valueint=QInputDialog::getInt(this,QString::fromLocal8Bit("������ͣ"),QString::fromLocal8Bit("������������ͣ�Ĵ��ڱ��"),1,1,8,1,&ok);
    if(ok){
      if(pause(valueint)) QMessageBox::information(this,QString::fromLocal8Bit("������ͣ"),
            QString::number(valueint)+QString::fromLocal8Bit("�Ŵ��ڽ�����ͣ")+QString::number(rest[valueint-1])+QString("s"),QMessageBox::Yes);
      else QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ǰӪҵ�����������٣����Ժ���������ͣ��"),QMessageBox::Yes);
    }
}

void MainWindow::timeUpdate()//��ʱ��ÿһ�봥��һ��
{
    timer = new QTimer();
    ui->systime->setDigitCount(9);
    ui->systime->setSegmentStyle(QLCDNumber::Flat);
    ui->systime->display(QDateTime::currentDateTime().toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(chTime()));
    timer->start(1000);
}

void MainWindow::chTime()
{
    ui->systime->display(QDateTime::currentDateTime().toString("hh:mm:ss"));//��Ļ�����ǰʱ��
    if(!isclose)
    {
        filetimes++;//ÿ��һ���ʱһ��
        if(iswork)
        {
            work();
            if(filetimes>=10){//ÿ10���ļ����һ��
                fileprint();
                filetimes=0;
            }
        }
        print();//ÿ�������Ļ��Ϣ
    }
    else {
        QMessageBox::information(this,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("Ӫҵ���Ѿ��°࣬������������ͳ��ϵͳ��"),QMessageBox::Yes);
        this->close();
        staticesw staticesw1;
        staticesw1.exec();
    }
}

void MainWindow::print()//������Ļ��Ϣ
{

    for(int i=0;i<8;i++)
    {
        if(vis[i]==-1) ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("��Ϣ")));
        else if(cur[i]!=-1||vis[i]==1) ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("����")));
        else ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("�ر�")));
        if(cur[i]!=-1)
        {
            if(i<=1&&printselect[i]) ui->window->setItem(1,i,new QTableWidgetItem("V"+QString::number(cur[i]/10)+QString::number(cur[i]%10)));
            else ui->window->setItem(1,i,new QTableWidgetItem(QString::number(cur[i]/100)+QString::number((cur[i]%100)/10)+QString::number(cur[i]%10)));
        }
        else ui->window->setItem(1,i,new QTableWidgetItem(QString("")));
    }
    ui->maxnum->setDigitCount(3);
    ui->maxvnum->setDigitCount(3);
    ui->waitnum->setDigitCount(3);
    ui->waitvnum->setDigitCount(3);
    ui->maxnum->display(maxnumber==-1?0:QString::number(maxnumber/100)+QString::number((maxnumber%100)/10)+QString::number(maxnumber%10));
    ui->maxvnum->display(vmaxnumber==-1?0:QString::number(vmaxnumber/10)+QString::number(vmaxnumber%10));
    ui->waitnum->display(counts);
    ui->waitvnum->display(vcounts);
    if(!tactic) ui->tacticrec->setText(QString::fromLocal8Bit("VIP����˳��������"));
    else ui->tacticrec->setText(QString::fromLocal8Bit("VIP���ڶ���������"));
    if(iswait){
        ui->isout->setText(QString::fromLocal8Bit("�ȴ��°��С�����"));
        if(!counts&&!vcounts){
            int i,oks=1;
            for(i=0;i<8;i++)
            {
                if(cur[i]!=-1){
                    oks=0;
                    break;
                }
            }
            if(oks) isclose=1;
        }
    }
    else if(iswork) ui->isout->setText(QString::fromLocal8Bit("����Ӫҵ�С�����"));
    else ui->isout->setText(QString::fromLocal8Bit("�ȴ��ϰ��С�����"));
}

void MainWindow::on_normalpush_clicked()//��ͨ�ͻ�������
{
    int oks=pnumber('G');
    if(oks==1) QMessageBox::information(this,QString::fromLocal8Bit("���"),
                         QString::fromLocal8Bit("���鵽�ĺ���Ϊ")+QString::number(maxnumber/100)+QString::number((maxnumber%100)/10)+QString::number(maxnumber%10)+QString::fromLocal8Bit("�����Ŷӵȴ��кš�"),QMessageBox::Yes);
    else if(oks==2) QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("Ӫҵ�������°࣬������������"),QMessageBox::Yes);
    else QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("����������ȴ����ȣ����Ժ�������"),QMessageBox::Yes);
}

void MainWindow::on_vippush_clicked()//vip�ͻ�������
{
    QString vipidstr=this->ui->vipidtext->text();
    QByteArray vipidstr2=vipidstr.toLatin1();
    char* vipids= vipidstr2.data();
    strcpy(vipid,vipids);
    int oks=pnumber('V');
    if(oks==0) QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("����������ȴ����ȣ����Ժ�������"),QMessageBox::Yes);
    else if(oks==-1) QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("����������ȷ��VIP�ͻ�ID��"),QMessageBox::Yes);
    else if(oks==1) QMessageBox::information(this,QString::fromLocal8Bit("���"),
                              QString::fromLocal8Bit("���鵽�ĺ���ΪV")+QString::number(vmaxnumber/10)+QString::number(vmaxnumber%10)+QString::fromLocal8Bit("�����Ŷӵȴ��кš�"),QMessageBox::Yes);
    else if(oks==-2) QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�޷���vip�ͻ����ϣ�"),QMessageBox::Yes);
    else if(oks==2) QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("Ӫҵ�������°࣬������������"),QMessageBox::Yes);
}

void MainWindow::on_towork_clicked()//������ʼӪҵ�ź�
{
    if(!iswork){
        iswork=1;
        QMessageBox::information(this,QString::fromLocal8Bit("Ӫҵ"),QString::fromLocal8Bit("���н���ʼӪҵ��"),QMessageBox::Yes);
    }
    else QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("����Ӫҵ�У��޷��ظ�������"),QMessageBox::Yes);
}

void MainWindow::on_action_3_triggered()
{
    on_towork_clicked();
}



void MainWindow::on_action_5_triggered()
{
    on_pausepush_clicked();
}

void MainWindow::on_action_6_triggered()
{
    on_outbank_clicked();
}

void MainWindow::on_actionVIP_triggered()
{
    vipinform1->show();
}
