#include<stdio.h>
struct process
{
    int process_name;
    int arrival_time, waiting_time, turn_time, priority,burst_time, burst_timecopy;
}queue1[10],queue2[10];
int main()
{
	struct process temp;
    int i,time=0,t1,t2,bu_t=0,largest,totalProcess,count=0,k,pf2=0,totalProcess2,n,pos,j,flag=0,y;
    float wait_time=0,turnaround_time= 0,average_waiting_time,average_turnaround_time;
    printf("\n Enter Total Number of Processes:\t");
    scanf("%d", &totalProcess);
    n=totalProcess;
    for(i=0;i<totalProcess;i++)
    {
    	printf("\nEnter Process name:-");
    	fflush(stdin);
        scanf("%d",&queue1[i].process_name);
        printf("\nEnter Details For processor %d:\n",queue1[i].process_name);
        printf("Enter Arrival Time:-");
        fflush(stdin);
        scanf("%d",&queue1[i].arrival_time);
        printf("Enter Burst Time:-");
        fflush(stdin);
        scanf("%d",&queue1[i].burst_time);
        queue1[i].burst_timecopy=queue1[i].burst_time;
        printf("Enter Priority:\t");
        fflush(stdin);
        scanf("%d",&queue1[i].priority);
    }
    printf("\nEnter Time Quantum for Fixed priority queue:-");
    scanf("%d",&t1);
    printf("\nEnter Time Quantum for Round Robin queue:-");
    scanf("%d",&t2);
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for(i=0;i<totalProcess;i++)
    {
        pos=i;
        for(j=i+1;j<totalProcess;j++)
        {
            if(queue1[j].arrival_time<queue1[pos].arrival_time)
                pos=j;
        }
        temp=queue1[i];
        queue1[i]=queue1[pos];
        queue1[pos]=temp;
    }
    time=queue1[0].arrival_time;
    for(i=0;totalProcess!=0;i++)
    {
    	while(count!=t1)
    	{
    		count++;
    		if(queue1[i].arrival_time<=time)
    		{
    			for(j=i+1;j<totalProcess;j++)
    			{
    				if(queue1[j].arrival_time==time && queue1[j].priority<queue1[i].priority)//pr<
    				{
    					queue2[pf2]=queue1[i];
						pf2++;
    					for(k=i; k<totalProcess-1;k++)
    						queue1[k]=queue1[k+1];
    					totalProcess--;
						count=0;
    					i=j-1;
    					j--;
					}
				}
			}
			time++;
			queue1[i].burst_time--;
			if(queue1[i].burst_time==0)
			{
				queue1[i].turn_time=time-queue1[i].arrival_time;
				queue1[i].waiting_time=queue1[i].turn_time-queue1[i].burst_timecopy;
				printf("%d\t|\t%d\t|\t%d\n",queue1[i].process_name,queue1[i].turn_time,queue1[i].waiting_time);
				wait_time+=time-queue1[i].waiting_time; 
    			turnaround_time+=time-queue1[i].turn_time;
    			for(k=i;k<totalProcess-1;k++)
    				queue1[k]=queue1[k+1];i--;
    			totalProcess--;
				count=t1;break;
			}
		}
		count=0;
		if(queue1[i].burst_time!=0)
		{
			queue2[pf2]=queue1[i];
			pf2++;
			for(k=i;k<totalProcess-1;k++)
    			queue1[k]=queue1[k+1];
    		totalProcess--;
		}
			if(i==totalProcess-1)
				i=-1;
	}
	
	totalProcess2=pf2;
	for(count=0;totalProcess2!=0;) 
	{ 
		if(queue2[count].burst_time<=t2&&queue2[count].burst_time>0) 
    	{ 
    		time+=queue2[count].burst_time; 
    		queue2[count].burst_time=0; 
    		flag=1; 
    	} 
    	else if(queue2[count].burst_time>0) 
    	{ 
    		queue2[count].burst_time-=t2; 
    		time+=t2; 
    	} 
    	if(queue2[count].burst_time==0&&flag==1) 
    	{ 
    		totalProcess2--; 
    		queue2[count].turn_time=time-queue2[count].arrival_time;
			queue2[count].waiting_time=queue2[count].turn_time-queue2[count].burst_timecopy; 
			printf("%d\t|\t%d\t|\t%d\n",queue2[count].process_name,queue2[count].turn_time,queue2[count].waiting_time); 
    		turnaround_time+=time-queue2[count].arrival_time; 
    		wait_time+=time-queue2[count].arrival_time-queue2[count].burst_timecopy;
    		for(k=count; k<totalProcess2;k++)
    			queue2[k]=queue2[k+1];count--;
    		flag=0; 
    	} 

    	if(count==totalProcess2-1) 
      		count=0; 
    	else 
    		count++; 
    }
    printf("\n Average Waiting Time= %f\n", wait_time/n); 
    printf("Avg Turnaround Time = %f\n" ,turnaround_time/n);   
}
