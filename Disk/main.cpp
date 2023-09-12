#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <math.h>

using namespace std;

int lcomp (const void * va, const void * vb)
{
if ( *(int*)va < *(int*)vb ) return -1;
if ( *(int*)va == *(int*)vb ) return 0;
if ( *(int*)va > *(int*)vb ) return 1;
}
void shift(int va[],const int vsize)
{
for(int li=1;li<=vsize;li++)
va[li-1]=va[li];
}
class schdisk
{
private :
int diskrq[1001];
int diskrq_sort[1001];
int numrq;
int discmax;
int headpo;
public :
schdisk()
{
discmax=5000;
}
//generating 1000 requests for the schdulling algorithm
void req_gen(int x)
{
numrq=1000;

//cout<<"\nInput current diskhead position : ";
//in>>diskrq[0];
diskrq[0]=x;
diskrq_sort[0]=diskrq[0];

headpo=1;

srand(time(NULL));
for(int li=1;li<=numrq;li++)
{
diskrq[li]=rand() % 5000 + 1;
cout<<diskrq[li]<<endl;
diskrq_sort[li]=diskrq[li];
}
qsort(diskrq_sort+1,numrq,sizeof(int),lcomp);

}

//fcfs schdulling procedure
int diskfcfs()
{
int mov_head=0;
for(int li=1;li<=numrq;li++)
mov_head+=abs(diskrq[li]-diskrq[li-1]);
return mov_head;
}
//sstf schdulling procedure
int disksstf()
{
int mov_head=0,vflag=0,nor=numrq;
int diskrq[101];
diskrq[0]=diskrq_sort[0];
for(int li=1;li<=numrq;li++)
{
if(diskrq_sort[li]>diskrq_sort[0]&&vflag==0)
vflag=li;
diskrq[li]=diskrq_sort[li];
}
while(nor)
{
if(vflag==0)
{
mov_head+=diskrq[0]-diskrq[nor];
diskrq[0]=diskrq[nor];
}
else if(vflag==1)
{
mov_head+=abs(diskrq[nor]-diskrq[0]);
break;
}
else if((diskrq[vflag]-diskrq[0])>(diskrq[0]-diskrq[vflag-1]))
{
mov_head+=diskrq[0]-diskrq[vflag-1];
diskrq[0]=diskrq[vflag-1];
vflag--;
shift(diskrq+vflag,nor-vflag);
}
else
{
mov_head+=diskrq[vflag]-diskrq[0];
diskrq[0]=diskrq[vflag];
shift(diskrq+vflag,nor-vflag);
}
nor--;
}
return (-1*mov_head);
}

//scan schdulling procedure
int SCAN()
{
int mov_head=0,vflag=0;

for(int li=1;li<=numrq;li++)
if(diskrq_sort[li]>diskrq_sort[0]&&vflag==0)
vflag=li;

if(headpo==1)
{
if(vflag==1)
mov_head+=diskrq_sort[numrq]-diskrq_sort[0];

else
{
mov_head+=discmax-diskrq_sort[0];
mov_head+=discmax-diskrq_sort[1];
}
}
else
{
if(vflag==0)
mov_head+=abs(diskrq_sort[numrq]-diskrq_sort[0]);

else
{
mov_head+=diskrq_sort[0];
mov_head+=diskrq_sort[numrq];
}
}
return mov_head;
}

~schdisk(){}
};
//main
int main(int argc, char *argv[])
{
schdisk myldisk;
int xi=atoi(argv[1]);
myldisk.req_gen(xi);
cout<<"Initial disk head is at :"<<xi<<endl;
cout<<"Total disk head movement in ";
cout<<"FCFS is:"<<myldisk.diskfcfs()<<endl;
cout<<"Total disk head movement in ";
cout<<"SSTF is: "<<myldisk.disksstf()<<endl;
cout<<"Total disk head movement in ";
cout<<"SCAN : "<<myldisk.SCAN()<<endl;
_getche();
   return 0;
}