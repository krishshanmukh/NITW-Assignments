#include<iostream>
using namespace std;

int data[100][100],in_degree[20],vis[20],d;

int find_min(int i)
{
	int j;
	for(j=i;j<d;j++)
	if(in_degree[j]==0&&!vis[j])
	break;
	if(j==d)
	return -1;
	else
	return j;
}

void input()
{
	cout<<"Enter no. of vertices: ";
	cin>>d;
	int k,j;
	for(k=0;k<d;k++)
	{
		vis[k]=0;in_degree[k]=0;
		for(j=0;j<d;j++)
	    data[k][j]=0;
	}
	cout<<"Enter edge vertices:";
	cin>>k;
	while(k!=-1)
	{
		cin>>j;
		data[k-1][j-1]=1;
		in_degree[j-1]++;
		cout<<"Enter edge vertices :";
		cin>>k;
	}
}

bool all_vis()
{
	int i;
	for(i=0;i<d;i++)
	if(vis[i]==0)
	break;
	if(i!=d)
	return false;
	else
	return true;
}

void red_adj(int i)
{
	for(int j=0;j<d;j++)
	if(data[i][j]==1)
	in_degree[j]--;
}

void topological_sort()
{
	while(!all_vis())
	{
		int i=0;
		cout<<"you can enter the vertex: ";
		i=find_min(i);
		while(i!=-1)
		{
			cout<<i+1<<" ";
			i=find_min(i+1);
		}
		cout<<endl;
		cout<<"Which vertex do you wish to enter ? ";
		cin>>i;
		vis[i-1]=1;
		red_adj(i-1);
	}
	cout<<"\nCongos!!! you have completed Topological sort :-)"<<endl;
}

int main()
{
	input();
	topological_sort();
	return 0;
}
