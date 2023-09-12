#include<iostream>
using namespace std;
typedef struct process
{
int pid,st,ft,prior;
int wt,tat,at,bt;
int flag;
}pr;

int n;
pr p[10];
void accept(int);
void fcfs();
void disp_gantt(int);
void sjf_sort();
void priority_sort();
void round_robin(int);

int main()
{
int ch,tq;
do
{
cout<<"\n\t Scheduling Algorithms ";
cout<<"\n\t1. FCFS\n\t2. SJF\n\t3. Priority Based\n\t4. Round Robin\n\t5. Exit";
cout<<"\n\t Enter your choice: ";
cin>>ch;
switch(ch)
{
case 1: accept(ch);
fcfs();
break;

case 2: accept(ch);
sjf_sort();
fcfs();
break;

case 3: accept(ch);
priority_sort();
fcfs();
break;

case 4: cout<<"\n\tEnter the Time Quantum: ";
cin>>tq;
accept(ch);
round_robin(tq);break;

case 5: break;
}
cout<<"\n\n\tPress any key to continue....";

}while(ch!=5);

}

void accept(int ch)
{
int i;
cout<<"\n\tHow many processes: ";
cin>>n;
cout<<"\tEnter the values\n";
if(ch==1 || ch==2)
{
cout<<"\n\tArrival Time and Burst Time\n";
for(i=0;i<n;i++)
{
cout<<"\tEnter for Process "<<i<<": ";
cin>>p[i].at>>p[i].bt;
p[i].pid=i;
}
}
if(ch==3)
{
cout<<"\n\tArrival Time , Burst Time and Priority\n";
for(i=0;i<n;i++)
{
cout<<"\tEnter for Process %d :"<<i;
cin>>p[i].at>>p[i].bt>>p[i].prior;
p[i].pid=i;
}
}
if(ch==4)
{
cout<<"\n\tArrival Time and Burst Time\n";
for(i=0;i<n;i++)
{
cout<<"\tEnter for Process %d :",i;
cin>>p[i].at>>p[i].bt;
p[i].pid=i;
}
}
}

void fcfs()
{
int i;
float avgtat=0,avgwt=0;
for(i=0;i<n;i++)
{
if(i==0)
{
p[i].st=i;
p[i].wt=p[i].st-p[i].at;
p[i].tat=p[i].wt+p[i].bt;
p[i].ft=p[i].st+p[i].bt;
}
else
{
p[i].st=p[i-1].ft;
p[i].wt=p[i].st-p[i].at;
p[i].tat=p[i].wt+p[i].bt;
p[i].ft=p[i].st+p[i].bt;
}
avgtat=avgtat+p[i].tat;
avgwt=avgwt+p[i].wt;
}
avgtat=avgtat/n;
avgwt=avgwt/n;
disp_gantt(n);
cout<<"\n\t** Average Turn Around Time**:"<<avgtat;
cout<<"\n\t** Average waiting time**:"<<avgwt;
}

void disp_gantt(int n)
{
int i;
cout<<"\n\tGANTT CHART\n ";
for(i=0;i<n;i++)
{
cout<<"\t P"<<p[i].pid;
}
cout<<"\n";
for(i=0;i<n;i++)
{
cout<<"\t"<<p[i].st;
}
cout<<"\t"<<p[i-1].ft;
cout<<"\n";
}

void sjf_sort()
{
int i,j;
pr temp;
for(i=0;i<n;i++)
{
for(j=0;j<n-i-1;j++)
{
if(p[j].bt>p[j+1].bt)
{
temp=p[j];
p[j]=p[j+1];
p[j+1]=temp;

}
}
}
}

void priority_sort()
{
int i,j;
pr temp;
for(i=0;i<n;i++)
{
for(j=0;j<n-i-1;j++)
{
if(p[j].prior>p[j+1].prior)
{
temp=p[j];
p[j]=p[j+1];
p[j+1]=temp;

}
}
}
}

void round_robin(int tq)
{
int allterminate=0,cnt=0,i;
int gt[30],ps[30],temp=0,pcnt=0;
float avgtat=0;
cout<<"\n\tGANTT CHART\n\n";
while(allterminate<n)
{
for(i=0;i<n;i++)
{
if(p[i].flag==0) //process incomplete
{
p[i].st=temp;
cnt++;
if(p[i].bt>=tq)//burst time > time slice
{

p[i].bt=p[i].bt-tq;
temp=temp+tq;
gt[cnt]=temp;
ps[pcnt]=p[i].pid;
pcnt++;
}
else
{ //burst time < time slice
temp=temp+p[i].bt;
gt[cnt]=temp;
p[i].bt=0;
ps[pcnt]=p[i].pid;
pcnt++;
}

if(p[i].bt==0)
{
allterminate++;
p[i].flag=1;
p[i].ft=temp;
}

if(p[i].flag==1)
{
p[i].tat=p[i].ft;
avgtat=avgtat+p[i].tat;
}
}//if

}//for

}//while
for(i=0;i<pcnt;i++)
{
cout<<"\t P"<<ps[i];
}
cout<<"\n\t0 ";
for(i=1;i<=cnt;i++)
{
cout<<"\t "<<gt[i];
}
avgtat=avgtat/n;
cout<<"\n\t** Average Turn Around Time**:"<<avgtat;
}