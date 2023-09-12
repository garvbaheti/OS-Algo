#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>

class process
{
 int pid,bt,wt,tat,pri;
 public:
 void getdata()
 {
  std::cout<<"Enter Process ID: ";
  std::cin>>pid;
  std::cout<<"Enter Burst Time: ";
  std::cin>>bt;
  std::cout<<"Enter Priority: ";
  std::cin>>pri;
  wt=0;
  tat=bt;
 }
 void showdata()
 {
  std::cout<<"Process ID: "<<pid<<"\n";
  std::cout<<"Burst Time: "<<bt<<"\n";
  std::cout<<"Waiting Time: "<<wt<<"\n";
  std::cout<<"Turnaround Time: "<<tat<<"\n";
 }
 int retbt()
 {
  return bt;
 }
 int retpid()
 {
  return pid;
 }
 int rettat()
 {
  return tat;
 }
 int retwt()
 {
  return wt;
 }
 int retpri()
 {
  return pri;
 }
 void putwt(int w)
 {
  wt=w;
 }
 void puttat(int t)
 {
  tat=t;
 }
};

class fcfs
{
 process p[10];
 int n,i;
 public:
 void getdata()
 {
  std::cout<<"Enter the number of processes: ";
  std::cin>>n;
  for(i=0;i<n;i++)
  {
   std::cout<<"\nEnter data for process "<<i+1<<"\n";
   p[i].getdata();
  }
 }
 void showdata()
 {
  for(i=0;i<n;i++)
  {
   std::cout<<"\nProcess "<<i+1<<"\n";
   p[i].showdata();
  }
 }
 void calctat()
 {
  p[0].puttat(p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].puttat(p[i-1].rettat()+p[i].retbt());
  }
 }
 void calcwt()
 {
  for(i=0;i<n;i++)
  {
   p[i].putwt(p[i].rettat()-p[i].retbt());
  }
 }
 void showavgwt()
 {
  float avgwt=0;
  for(i=0;i<n;i++)
  {
   avgwt+=p[i].retwt();
  }
  std::cout<<"\nAverage Waiting Time: "<<avgwt/n;
 }
 void showavgtat()
 {
  float avgtat=0;
  for(i=0;i<n;i++)
  {
   avgtat+=p[i].rettat();
  }
  std::cout<<"\nAverage Turnaround Time: "<<avgtat/n;
 }
};

class sjf
{
 process p[10];
 int n,i,j;
 public:
 void getdata()
 {
  std::cout<<"Enter the number of processes: ";
  std::cin>>n;
  for(i=0;i<n;i++)
  {
   std::cout<<"\nEnter data for process "<<i+1<<"\n";
   p[i].getdata();
  }
 }
 void showdata()
 {
  for(i=0;i<n;i++)
  {
   std::cout<<"\nProcess "<<i+1<<"\n";
   p[i].showdata();
  }
 }
 void sort()
 {
  process temp;
  for(i=0;i<n-1;i++)
  {
   for(j=i+1;j<n;j++)
   {
    if(p[i].retbt()>p[j].retbt())
    {
     temp=p[i];
     p[i]=p[j];
     p[j]=temp;
    }
   }
  }
 }
 void calctat()
 {
  sort();
  p[0].puttat(p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].puttat(p[i-1].rettat()+p[i].retbt());
  }
 }
 void calcwt()
 {
  sort();
  p[0].putwt(p[0].rettat()-p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].putwt(p[i].rettat()-p[i].retbt());
  }
 }
 void showavgwt()
 {
  float avgwt=0;
  for(i=0;i<n;i++)
  {
   avgwt+=p[i].retwt();
  }
  std::cout<<"\nAverage Waiting Time: "<<avgwt/n;
 }
 void showavgtat()
 {
  float avgtat=0;
  for(i=0;i<n;i++)
  {
   avgtat+=p[i].rettat();
  }
  std::cout<<"\nAverage Turnaround Time: "<<avgtat/n;
 }
};

class rr
{
 process p[10];
 int n,i,j,q,r;
 public:
 void getdata()
 {
  std::cout<<"Enter the number of processes: ";
  std::cin>>n;
  for(i=0;i<n;i++)
  {
   std::cout<<"\nEnter data for process "<<i+1<<"\n";
   p[i].getdata();
  }
 }
 void showdata()
 {
  for(i=0;i<n;i++)
  {
   std::cout<<"\nProcess "<<i+1<<"\n";
   p[i].showdata();
  }
 }
 void calctat()
 {
  p[0].puttat(p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].puttat(p[i-1].rettat()+p[i].retbt());
  }
 }
 void calcwt()
 {
  p[0].putwt(p[0].rettat()-p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].putwt(p[i].rettat()-p[i].retbt());
  }
 }
 void showavgwt()
 {
  float avgwt=0;
  for(i=0;i<n;i++)
  {
   avgwt+=p[i].retwt();
  }
  std::cout<<"\nAverage Waiting Time: "<<avgwt/n;
 }
 void showavgtat()
 {
  float avgtat=0;
  for(i=0;i<n;i++)
  {
   avgtat+=p[i].rettat();
  }
  std::cout<<"\nAverage Turnaround Time: "<<avgtat/n;
 }
};

class pri
{
 process p[10];
 int n,i,j;
 public:
 void getdata()
 {
  std::cout<<"Enter the number of processes: ";
  std::cin>>n;
  for(i=0;i<n;i++)
  {
   std::cout<<"\nEnter data for process "<<i+1<<"\n";
   p[i].getdata();
  }
 }
 void showdata()
 {
  for(i=0;i<n;i++)
  {
   std::cout<<"\nProcess "<<i+1<<"\n";
   p[i].showdata();
  }
 }
 void sort()
 {
  process temp;
  for(i=0;i<n-1;i++)
  {
   for(j=i+1;j<n;j++)
   {
    if(p[i].retpri()>p[j].retpri())
    {
     temp=p[i];
     p[i]=p[j];
     p[j]=temp;
    }
   }
  }
 }
 void calctat()
 {
  sort();
  p[0].puttat(p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].puttat(p[i-1].rettat()+p[i].retbt());
  }
 }
 void calcwt()
 {
  sort();
  p[0].putwt(p[0].rettat()-p[0].retbt());
  for(i=1;i<n;i++)
  {
   p[i].putwt(p[i].rettat()-p[i].retbt());
  }
 }
 void showavgwt()
 {
  float avgwt=0;
  for(i=0;i<n;i++)
  {
   avgwt+=p[i].retwt();
  }
  std::cout<<"\nAverage Waiting Time: "<<avgwt/n;
 }
 void showavgtat()
 {
  float avgtat=0;
  for(i=0;i<n;i++)
  {
   avgtat+=p[i].rettat();
  }
  std::cout<<"\nAverage Turnaround Time: "<<avgtat/n;
 }
};

signed main()
{
 int ch;
 fcfs f;
 sjf s;
 rr r;
 pri p;
 do
 {
  std::cout<<"\n1.First Come First Serve\n2.Shortest Job First\n3.Round Robin\n4.Priority\n5.Exit\n";
  std::cout<<"Enter your choice: ";
  std::cin>>ch;
  switch(ch)
  {
   case 1:
   {
    f.getdata();
    f.calctat();
    f.calcwt();
    f.showdata();
    f.showavgwt();
    f.showavgtat();
    break;
   }
   case 2:
   {
    s.getdata();
    s.calctat();
    s.calcwt();
    s.showdata();
    s.showavgwt();
    s.showavgtat();
    break;
   }
   case 3:
   {
    r.getdata();
    r.calctat();
    r.calcwt();
    r.showdata();
    r.showavgwt();
    r.showavgtat();
    break;
   }
   case 4:
   {
    p.getdata();
    p.calctat();
    p.calcwt();
    p.showdata();
    p.showavgwt();
    p.showavgtat();
    break;
   }
   case 5:
   {
    exit(0);
   }
   default:
   {
    std::cout<<"\nInvalid choice\n";
   }
  }
 }while(ch!=5);
 getch();
 
}