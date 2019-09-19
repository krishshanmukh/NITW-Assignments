#include<iostream>
using namespace std;

class stack
{
	int elt[15];
	int top;
	public :
		stack()
		{
			top=-1;
		}
		int pop();
		void push(int i);
		int isempty();
};

void stack :: push(int i)
{
	if(top<15)
	elt[++top]=i;
	else
	cout<<"Stack is full!";
}

int stack :: pop()
{
	if(top>=0)
	return elt[top--];
	else
	return -1;
}

int stack :: isempty()
{
	if(top>=0)
	return 0;
	else
	return 1;
}


int data[100][100],data1[100][100],d,no=0,count=1,vert=0,ctr=0,num1[100];
stack s;

int check(int data[],int d)
{
	int i;
	for(i=0;i<d;i++)
	{
		if(data[i]!=0)
			break;
	}
	if(i==d)
	return 1;
	else
	return 0;
}

int all_vis_data(int data[],int vis[])
{
	int i;
	for(i=0;i<d;i++)
	{
		if(data[i]!=0&&vis[i]==0)
		break;
	}
	if(i==d)
	return 1;
	else
	return 0;
}

void reverse_graph()
{
	for(int i=0;i<d;i++)
	for(int j=0;j<d;j++)
	{
		int temp=data[i][j];
		data[i][j]=data[j][i];
		data[j][i]=temp;
	}
}

void make_zero(int data[])
{
	for(int i=0;i<d;i++)
	data[i]=0;
}

int find_vertex(int vis[])
{
	int i;
	for(i=0;i<d;i++)
	{
		if(vis[i]==0)
		break;
	}
	return i;
}

int find_next(int num[],int vis[])
{
	int i;
	for(i=d-1;i>=0;i--)
	{
		if(vis[num[i]]==0)
		break;
	}
	return num[i];
}

void strong_comp(int num[],int vis[],int vertex)
{
	--no;
	s.push(vertex);
	vis[vertex]=1;
	if(!check(data1[vertex],d)&&!all_vis_data(data1[vertex],vis))
	{
		for(int i=0;i<d;i++)
		if(data1[vertex][i]!=0&&vis[i]!=1)
		{
			strong_comp(num,vis,i);
		}
	}
	if(vertex==vert)
	{
		while(!s.isempty())
		{
	      	num1[ctr++]=s.pop();
	     	cout<<num1[ctr-1]+1<<" ";
	    }
	    cout<<"}  \n{ ";
	    if(no>=0)
	    {
	        vertex=find_next(num,vis);
		    vert=vertex;
		    strong_comp(num,vis,vertex);
	    }
	    else;
	}		
}

void strong(int vis[],int num[],int vertex)
{
	int m=0;
	no++;
	cout<<vertex+1<< " ";
	if(!check(data[vertex],d)&&!all_vis_data(data[vertex],vis))
	{
		s.push(vertex);
		vis[vertex]=1;
		for(int i=0;i<d;i++)
		{
			if(data[vertex][i]!=0&&vis[i]!=1)
			{
				m=1;
				//cout<<vertex<<" "<<no<" ";
				strong(vis,num,i);
			}
		}
	}
	else
	{
		s.push(vertex);
		vis[vertex]=1;
		//cout<<vertex<<" ";
		//cout<<no<<" ";
	}
	if(vertex==vert)
	{
		while(!s.isempty())
		{
	        num[ctr++]=s.pop();
	        cout<<num[ctr-1]<<" ";
	    }
	    if(no!=d)
	    {
	        vertex=find_vertex(vis);
		    vert=vertex;
		    strong(vis,num,vertex);
	    }
	    else
		{  
			//if(count++==1)
//			reverse_graph();
//			make_zero(vis);
//			cout<<"\n{ ";
		}
	}
}

int main()
{
	cout<<"Enter no. of vertices: ";
	cin>>d;
	const int v=d;
	int vis[v],num[v],j;
	make_zero(vis);
	make_zero(num);
	for(int i=0;i<d;i++)
	{
	    for(int j=0;j<d;j++)
	    data[i][j]=0;
	}
	for(int k=0;k<d;k++)
	{
		cout<<"Enter adjacent vertices of "<<k+1<<" : ";
		cin>>j;
		while(j!=-1)
		{
		    data[k][j-1]=1;
		    cin>>j;
		}
	}
	vert=0;
	strong(vis,num,0);
	vert=num[--no];
	for(int i=0;i<d;i++)
	{
	    for(int j=0;j<d;j++)
	    data1[i][j]=0;
	}
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		if(data[i][j]==1)
		data1[j][i]=1;
	}
	for(int i=0;i<d;i++)
	{
	    for(int j=0;j<d;j++)
	    cout<<data1[i][j]<<" ";
	    cout<<endl;
	}
	make_zero(vis);
	ctr=0;
	cout<<"\n{ ";
	//for(int i=0;i<d;i++)
//	cout<<num[i]<<" "<<vis[num[i]]<<" ";
	strong_comp(num,vis,vert);
	cout<<"\b\b  ";
	return 0;
}
