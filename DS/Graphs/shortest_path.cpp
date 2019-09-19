#include<iostream>
using namespace std;

//void input(int d,int A[][d])
//{
//	cout<<"Enter the adjacency matrix: ";
//	for(int i=0;i<d;i++)
//	for(int j=0;j<d;j++)
//	cin>>A[i][j];
//}

bool is_vis(int A[],int i)
{
	if(A[i]==-1)
	return false;
	else 
	return true;
}

int find_min(int dis[],int vis[],int d)
{
	int min=0;
	int j;
	for(int i=0;i<d;i++)
	{
		if(dis[i]!=0)
		{
			//cout<<dis[i];
			if((dis[i]<min||min==0)&&!is_vis(vis,i))
			{
			    min=dis[i];
			    j=i;
			}
		}
	}
	return j;
}

void make_empty(int dis[],int via[],int vis[],int d)
{
	for(int i=0;i<d;i++)
	{
		dis[i]=0;
		via[i]=-1;
		vis[i]=-1;
	}
}

void shortest_path(int data[],int dis[],int via[],int vis[],int d,int &cur,int end)
{
	int cd;
	if(cur!=end)
	{
		cd=dis[cur];
		for(int i=0;i<d;i++)
		{
			if(data[i]!=0&&i!=cur)
			{
				if(!is_vis(vis,i)&&dis[i]==0)
				{
					dis[i]=cd+data[i];
					//cout<<dis[i]<<" ";
					via[i]=cur;
				}
				else
				{
					cd+=data[i];
					if(cd<dis[i])
					{
						dis[i]=cd;
						//cout<<cd;
						via[i]=cur;
					}
					cd=dis[cur];
				}
			}
		}
		vis[cur]=1;
		//cout<<cur+1<<" ";
		cur=find_min(dis,vis,d);
		//cout<<cur+1<<" ";
	}
}

void display(int via[],int end)
{
	if(via[end]!=-1)
	{
		//cout<<via[end];
		display(via,via[end]);
		cout<<via[end]+1<<" ";
	}
}

int main()
{
	int v;
	cout<<"Enter no. of vertices: ";
	cin>>v;
	const int d=v;
	int data[d][d],dis[d],vis[d],via[d],cur,end;
	//input(data,d);
	cout<<"Enter the adjacency matrix: ";
	for(int i=0;i<d;i++)
	for(int j=0;j<d;j++)
	cin>>data[i][j];
	make_empty(dis,via,vis,d);
	{
		cout<<"Enter starting and ending vertices: ";
		cin>>cur>>end;
		cur--;
		end--;
		while(cur!=end)
		shortest_path(data[cur],dis,via,vis,d,cur,end);
		display(via,end);
		cout<<end+1;
		make_empty(dis,via,vis,d);
	}
	return 0;
}
