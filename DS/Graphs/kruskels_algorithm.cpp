#include<iostream>
using namespace std;

int d,data[100][100],S[100];

struct heap
{
	int u;
	int v;
	int wt;
};

void heapcreate(heap H[],int i)
{
	if(i>0)
	{
		if(H[i].wt<H[(i-1)/2].wt)
		{
			heap temp;
			temp=H[(i-1)/2];
			H[(i-1)/2]=H[i];
			H[i]=temp;
			heapcreate(H,((i-1)/2));
		}
	}
}

void delheapify(heap H[],int i,int in)
{
	if(2*i+2<=in)
	{
		int a=(H[2*i+1].wt>H[2*i+2].wt?(2*i+2):(2*i+1));
		if(H[i].wt>H[2*i+1].wt||H[i].wt>H[2*i+2].wt)
		{
			swap(H[i],H[a]);
			delheapify(H,a,in);
		}
	}
	else if(2*i+1<=in)
	{
		if(H[i].wt>H[2*i+1].wt)
		swap(H[i],H[2*i+1]);
	}
}

heap heapsort(heap H[],int &s)
{
	heap S=H[0];
	H[0]=H[s--];
	delheapify(H,0,s);
	return S;
}

int find(int x)
{
	return (S[x]==0?x:find(S[x]));
}

void union_set(int x,int y)
{
	S[find(y)]=find(x);
}

int findandcompress(int x)
{
	return (S[x]==0? x : findandcompress(S[x]));
}

int main()
{
	cout<<"Enter no. of vertices: ";
	cin>>d;
	const int v=d;
	heap H[30];
	int i=-1,j,k,wt;
	for(k=0;k<d;k++)
	{
	    for(j=0;j<d;j++)
	    data[k][j]=0;
	}
	cout<<"Enter vertices and wt of :";
	cin>>k;
	while(k!=0)
	{
		cin>>j;
		cin>>wt;
		data[k-1][j-1]=wt;
		data[j-1][k-1]=wt;
		H[++i].wt=wt;
		H[i].u=k;
		H[i].v=j;
		heapcreate(H,i);
		cout<<"Enter vertices and wt of :";
		cin>>k;
	}
	for(j=1;j<=d;j++)
	S[j]=0;
	int ac=1,sum=0;
	while(ac<d)
	{
		heap M=heapsort(H,i);
		if(findandcompress(M.u)!=findandcompress(M.v))
		{
			ac++;
			cout<<endl<<M.u<<"-"<<M.v<<" = "<<M.wt;
			sum=sum+M.wt;
			union_set(M.u,M.v);
		}
	}
	cout<<"\nthe total cost is : "<<sum;
	return 0;
}
