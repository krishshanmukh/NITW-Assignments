#include<iostream>
using namespace std;

bool is_vis(int A[],int i)
{
	if(A[i]==-1)
	return false;
	else 
	return true;
}

bool all_ver(int A[],int d)
{
	int i;
	for(i=0;i<d;i++)
	{
	    if(A[i]==-1)
	    {
	        return false;
	        break;
	    }
	}
	if(i==d)
	return true;
}

int minimum;

int find_minimum(int data[],int vis[],int &ver,int d)
{
	for(int i=0;i<d;i++)
	{
		if(data[i]!=0)
		{
			if(minimum==0)
			{
			    minimum=data[i];
			    ver=i;
			}
			else if(minimum>data[i]&&vis[i]==-1)
			{
				minimum=data[i];
			    ver=i;
			}
		}
	}
}

void make_empty(int dis[],int via[],int vis[],int ver[],int d)
{
	for(int i=0;i<d;i++)
	{
		dis[i]=0;
		via[i]=-1;
		vis[i]=-1;
		ver[i]=-1;
	}
}

void display(int via[],int d)
{
	for(int i=0;i<d;i++)
	{
		if(via[i]!=-1)
		cout<<i+1<<"-"<<via[i]+1<<endl;
	}
}

bool is_full(int dis[],int d,int cur)
{
	int i=0;
	for(int i=0;i<d;i++)
	{
		if(dis[i]==0&&i!=cur)
		break;
	}
	if(i==d)
	return true;
	else
	return false;
}

int main()
{
	int v;
	cout<<"Enter no. of vertices: ";
	cin>>v;
	const int d=v;
	int data[d][d],dis[d],vis[d],via[d],ver[d],cur,m,j,vert,vertex1,vertex2,p,i;
	cout<<"Enter the adjacency matrix: ";
	for(int k=0;k<d;k++)
	for(int j=0;j<d;j++)
	cin>>data[k][j];
	make_empty(dis,via,vis,ver,d);
	cout<<"Enter starting vertex: ";
	cin>>cur;
	cur--;
	i=0;
	ver[0]=cur;
	vis[cur]=1;
	i++;
	while(!all_ver(ver,d))
	{
    	j=0;
		minimum=0;
		vert=-1;
		while(j<i)
		{
			p=minimum;
			find_minimum(data[ver[j]],vis,vert,d);
			if(p!=minimum)
			{
			    vertex2=vert;
			    vertex1=ver[j];
			}
			j++;
		}
		if(via[vertex2]==-1)
		{
			via[vertex2]=vertex1;
		    ver[i++]=vertex2;
		    vis[vertex2]=1;
		}
		data[vertex1][vertex2]=0;
		data[vertex2][vertex1]=0;
	}
	display(via,d);
	return 0;
}
