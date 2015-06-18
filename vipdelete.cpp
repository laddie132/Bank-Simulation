#include "vipdelete.h"
#include "ui_vipdelete.h"
#include <qmessagebox.h>
#include "bank.h"

vipdelete::vipdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipdelete)
{
    ui->setupUi(this);
}

vipdelete::~vipdelete()
{
    delete ui;
}

void vipdelete::on_pushButton_clicked()
{
    this->close();
}

void vipdelete::on_pushButton_2_clicked()//ɾ��һ��vip�ͻ�
{
    customer a,temp[10000],b;
    FILE *fptr;
    if((fptr=fopen("vip.dat","r+b"))==NULL){
        QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�޷���vip�ͻ����ϣ�"),QMessageBox::Yes);
    }
    else{
        QByteArray temps;
        char* tempstr;
        temps=ui->name->text().toLatin1();
        tempstr=temps.data();
        strcpy(a.name,tempstr);
        rewind(fptr);
        fread(&b,sizeof(customer),1,fptr);
        int i=0;
        while(!feof(fptr)){
            if(strcmp(b.name,a.name)){
                temp[i++]=b;
            }
            fread(&b,sizeof(customer),1,fptr);
        }
        fclose(fptr);
        if((fptr=fopen("vip.dat","w"))==NULL){
            QMessageBox::warning(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�޷���vip�ͻ����ϣ�"),QMessageBox::Yes);
        }
        else{
            fwrite(temp,sizeof(customer),i,fptr);
            fclose(fptr);
            this->close();
            QMessageBox::information(this,QString::fromLocal8Bit("��ʾ"),QString::fromLocal8Bit("VIP�ͻ�ɾ���ɹ���"),QMessageBox::Yes);
        }
    }
}
