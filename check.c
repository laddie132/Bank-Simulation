#include<stdio.h>
#include<time.h>

extern int counts,vcounts,current,vcurrent,flag,cstart;
extern int vis[8],cur[8],tactic;

void check()
{
	int curwin=0,vcurwin=0,i;
	for(i=0;i<2;i++)//���㵱ǰ����VIP����������ͨ������ 
	   if(vis[i]==1) vcurwin++;
    for(i=2;i<8;i++)
       if(vis[i]==1) curwin++;
    if(counts>=(3*curwin)&&curwin<6){//��̬������ͨ������ 
    	for(i=2;i<8;i++)
    	{
	    	if(vis[i]==0){
	    		vis[i]=1;
	    		break;
	    	}
	    }
	}
    if(counts<curwin*2){
    	curwin=0;
    	for(i=2;i<8;i++)
    	{
	    	if(vis[i]==1){
	    		curwin++;
	    		if(curwin>3) vis[i]=0;
	    	}
	    }
    } 
    if(vcounts>3){                  //��̬����VIP������ 
    	for(i=0;i<2;i++) if(vis[i]==0) vis[i]=1;
	}
    if(vcounts<3&&flag){
    	cstart=time(NULL);
    	flag=0;
    }
	if(!vcounts) tactic=0;
	else tactic=1;
}
