#include<stdio.h>
#include<stdlib.h>
#include<time.h>


extern time_t rest[8],rstart[8];
extern int cur[8],vis[8],MinRestSec,MaxRestSec;

int pause(int restnum)
{
    int curwin=0,vcurwin=0,i;
	for(i=0;i<2;i++)//���㵱ǰ����VIP����������ͨ������ 
	   if(vis[i]==1) vcurwin++;
    for(i=2;i<8;i++)
       if(vis[i]==1) curwin++;
    if((restnum>=1&&restnum<=2&&vcurwin==2)||(restnum>=3&&restnum<=8&&curwin>3)){
    	if(cur[restnum-1]!=-1) vis[restnum-1]=-2;
    	else{
	    	vis[restnum-1]=-1;
	    	rstart[restnum-1]=time(NULL);
	    }
    	rest[restnum-1]=(rand()%(MaxRestSec-MinRestSec+1))+MinRestSec;
        return 1;
    }
    return 0;
}
