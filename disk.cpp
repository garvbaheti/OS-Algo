#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
typedef long long int ll;
#define pb push_back
typedef vector<int> v;

vector<int> arr;
int head=0;

int sum=0;

int FCFS()
{
	int sum=0;
	rep(i,arr.size())
	{
		sum=sum+abs(head-arr[i]);
		head=arr[i];
	}
	return sum;
}


int SSTF()
{
	int ans=0;
	int n=arr.size();
	v visited(n,0);

	rep(i,n)
	{
		int mini=INT_MAX;
		int index=-1;
		
		rep(j,n)
		{
			if(abs(head-arr[j])<mini && visited[j]!=1)
			{
				mini=abs(head-arr[j]);
				index=j;
			}
		}
		visited[index]=1;
		ans=ans+mini;
		head=arr[index];
	}
	return ans;
}



struct compare
{
	bool operator()(int a,int b)
	{
		if(abs(head-a)==abs(head-b))
			return a>b;
		else
		return abs(head-a)>abs(head-b);
	}
};



int SCAN()
{
	int ans=0;
	int n=arr.size();
	sort(arr.begin(),arr.end(),compare());

	rep(i,n)
	{
		ans=ans+abs(head-arr[i]);
		head=arr[i];
	}
	return ans;
}



int main()
{
	arr.pb(25);
	arr.pb(155);
	arr.pb(10);
	arr.pb(65);
	arr.pb(190);
	arr.pb(40);
	arr.pb(5);
	arr.pb(100);
	arr.pb(15);
	arr.pb(20);
	
	cout<<"The sum of tracks traversed in FCFS is "<<FCFS()<<endl;
	cout<<"The sum of tracks traversed in SSTF is "<<SSTF()<<endl;
	cout<<"The sum of tracks traversed in SCAN is "<<SCAN()<<endl;
}