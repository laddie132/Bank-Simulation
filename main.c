#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<graphics.h> 
#include "bank.h"

char ch;
tongji sta[8];//����ÿ������ͳ�ƽ��
time_t cstart,start[8],end[8],rest[8],rstart[8];//end[8]����ÿ���ͻ�����ʱ��
int MaxSeqLen=0,MinSec=0,MaxSec=0,MinRestSec=0,MaxRestSec=0,VIPSERVLen=0;
int vis[]={1,0,1,1,1,0,0,0}; //���浱ǰ����"�ϰ�"�򡰹رա�״̬����Ϣ��״̬
int cur[]={-1,-1,-1,-1,-1,-1,-1,-1};//���浱ǰ���ڷ���ͻ����
int maxnumber=-1,counts=0,vmaxnumber=-1,vcounts=0,current=-1,vcurrent=-1,iswait=0,isclose=0,flag=1,tactic=1;

int main()
{
	system("color 71"); 
	printf("\t\tWelcome to the vitual bank system!\n\n\n\n\n");
	printf("X:VIP update\n\n");
	printf("W:Enter bank system\n\n");
	printf("Q:Quit\n\n\n\n");
	printf("Please input 'X' 'Q' or 'W' to choose the function you want.\n\n");
	scanf("%c",&ch);
	if(ch=='W'||ch=='X'){
		if(ch=='X') vip();//vip�ͻ����ϸ���
        srand((int)time(0));
        memset(sta,0,sizeof(sta));
     	cconfig();//�������ļ��е������
        DWORD ThreadID1 = 1;
        HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)work,NULL,0,&ThreadID1);
        DWORD ThreadID2 = 2;
        HANDLE hRead2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)reprint,NULL,0,&ThreadID2);
        CloseHandle(hRead1);
        CloseHandle(hRead2);
        while(scanf("%c",&ch)){
         	if(ch=='G'||ch=='V'){//�¿ͻ�������
    	    	pnumber();
    	    }
        	else if(ch=='R'){//������ͣ
    	    	pause();
    	    }
        	else if(ch=='Q'){//�ȴ��°�״̬
          		printf("------The bank will enter the state of waitting.-----\n\n");
        		iswait=1;
    	    	break;
    	    }
    	    else if(ch!='\n') printf("-----illegal input!------\n\n");
        }
        int isok=0,i=0;
        while(counts!=0||vcounts!=0||!isok)
        {
        	for(i=0,isok=1;i<8;i++)
        	{
	        	if(cur[i]!=-1){
	        		isok=0;
	        		break;
	        	}
	        }
        	Sleep(1000);
        }
        statices();//���ͳ�ƽ���ļ�
        printf("--------The bank will be closed.--------\n\n");
	}
	else if(ch!='Q') printf("-------illegal input!------\n\n");
	isclose=1;
	system("pause");
	return 0;
}
void reprint()//ÿ��10���ӡһ�������������
{
	printf("\n\n****Please input 'G','V','Rx' or 'Q' to choose your function.****\n\n");
	Sleep(1000);
	while(!isclose){
		print();
		Sleep(10000);
	}
}
