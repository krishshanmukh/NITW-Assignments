#include<iostream>
#include<fstream>
using namespace std;

int data[20][20],vis[20],dfs[20],num[20],count=0,d,via[20],print[20];

int find(int i,int &m)
{
	int j;
	for(j=0;j<d;j++)
	if(data[i][j]!=0&&vis[j]!=1)
	break;
	if(j!=d&&m==0)
	return j;
	else if(j!=d&&m==1)
	return i;
	else if (count<d)
	{
		m=1;
		return find(via[i],m);
	}
}

int find_low(int i,int low)
{
	int min=num[i];
	for(int j=0;j<d;j++)
	{
		if(data[i][j]!=0&&via[i]!=j)
		if(num[j]<min)
		min=num[j];
	}
	if(low<min&&low!=-1)
	min=low;
	return min;
}

int articulation_points(int i,int r)
{
	int t=0;
	if(vis[i]!=1)
	{
		vis[i]=1;via[i]=r;
		num[i]=++count;t=1;
	}
	int m=0;
	int low=-1;
	if(count<d)
	{
		int j=find(i,m);//cout<<i+1<<" "<<j+1<<"- ";
		low=articulation_points(j,i);
	}
	if(print[i]!=1&&((i!=0&&low>=num[i])||(i==0&&low>num[i])))
	{
		cout<<i+1<<" ";
		print[i]=1;
	}
	if(t==1)
	{
		num[i]= find_low(i,low);
		return num[i];
	}
	else return -1;
}

int main()
{
	ifstream in("data.txt");
	//cout<<"Enter no. of vertices: ";
	in>>d;
	int k,j;
	for(k=0;k<d;k++)
	for(j=0;j<d;j++)
    data[k][j]=0;
	//cout<<"Enter edge vertices:";
	in>>k;
	while(k!=-1)
	{
		in>>j;//cout<<k<<" "<<j<<" - ";
		data[k-1][j-1]=1;
		data[j-1][k-1]=1;
		//cout<<"Enter edge vertices :";
		in>>k;
	}in.close();
	articulation_points(0,-1);
	return 0;
}
