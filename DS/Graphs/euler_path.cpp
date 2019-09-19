#include<iostream>
using namespace std;

bool is_vis(int A[],int i)
{
	if(A[i]==-1)
	return false;
	else 
	return true;
}

int minimum;

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

int check(int A[],int d)
{
	int i;
	for(i=0;i<d;i++)
	{
		if(A[i]!=0)
		{
			return i;
			break; 
		}
	}
	if(i==d)
	return -1;
}

void splice(int A[],int B[],int i,int x,int y)
{
	for(int j=x;j>i;j--)
	A[j+y-1]=A[j];
	for(int j=0;j<y;j++)
	A[j+i]=B[j];
}

int main()
{
	int v;
	cout<<"Enter no. of vertices: ";
	cin>>v;
	const int d=v;
	int data[d][d],dis[d],vis[d],via[d],ver[3*d],res[3*d],cur,j,vert,vertex1,vertex2,count=0,i,no=0,m=0;
	int choice=0,distance,euler[3*d];
	make_empty(dis,via,vis,ver,d);
	for(int i=0;i<d;i++)
	{
	    for(int j=0;j<d;j++)
	    data[i][j]=0;
	}
	do
	{
		cout<<"Enter vertex nos:  ";
		cin>>i>>j;
		data[i-1][j-1]=1;
		data[j-1][i-1]=1;
		count++;
		cout<<"Enter 1 to enter more data: ";
		cin>>choice;
	}while(choice==1);
	for(int i=0;i<d;i++)
	{
	    for(int j=0;j<d;j++)
	    cout<<data[i][j]<<" ";
	    cout<<endl;
	}
	cout<<"Enter starting vertex: ";
	cin>>cur;
	cur--;
	i=0;
	vert=cur;
	//q.enqueue(i);
	ver[i++]=cur;
	vis[cur]=1;
	while(count!=0)
	{
    	for(int k=0;k<d;k++)
		{
			if(data[vert][k]!=0)
			{
				//q.enqueue(k);
				data[vert][k]=0;
				data[k][vert]=0;
				count--;
				ver[i++]=k;
				vert=k;
				//cout<<k;
				break;
			}
		}
		while(vert!=cur&&check(data[vert],d)!=-1)
		{
			for(int k=0;k<d;k++)
			{
				if(data[vert][k]!=0)
				{
					//q.enqueue(k);
					data[vert][k]=0;
					data[k][vert]=0;
					count--;
					ver[i++]=k;
					vert=k;
					//cout<<k;
					k=0;
					break;
				}
			}
		}
		//cout<<no<<i;
		splice(res,ver,m,no,i);
		//for(int k=0;k<i;k++)
//		cout<<"("<<ver[k]+1<<")";
		i--;
		no+=i;
		for(int k=0;k<=no;k++)
		{
			vert=check(data[res[k]],d);
			if(vert!=-1&&!is_vis(vis,res[k]))
			{
				i=0;
				m=k;
				vert=res[k];
				cur=vert;
				ver[i++]=vert;
				break;
			}
		}
	}
	for(int k=0;k<=no;k++)
	cout<<res[k]+1<<"-";
	cout<<"\b ";
	//display(via,d);
	return 0;
}
