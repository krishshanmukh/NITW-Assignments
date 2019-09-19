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

int check(int A[],int d)
{
	int i;
	for(i=0;i<d;i++)
	{
		if(A[i]!=0)
		{
			return 1;
			break;
		}
	}
	if(i==d)
	return 0;
}

int main()
{
	int v;
	stack s,s1;
	cout<<"Enter no. of vertices: ";
	cin>>v;
	const int d=v;
	int data[d][d],dis[d],vis[d],cur,vertex,count,i=0,m;
	//input(data,d);
	for(int k=0;k<d;k++)
	{
		for(int j=0;j<d;j++)
		data[k][j]=0;
	}
	do
	{
	    cout<<"Enter the vertex nos: ";
	    cin>>cur>>vertex;
	    data[vertex-1][cur-1]=1;
	    data[cur-1][vertex-1]=1;
	    cout<<"1 to continue: ";
	    cin>>cur;
	}while(cur==1);
	for(int k=0;k<d;k++)
	{
		vis[k]=0;
	}
	cout<<"Enter starting vertex: ";
	cin>>cur;
	cur--;
	vis[cur]=1;
    s.push(cur);
    i++;
    while(i!=d)
    {
    	vertex=s.pop();
		while(!check(data[vertex],d))
		{
			s1.push(vertex);
			vertex=s.pop();
		}
		s.push(vertex);
		m=s1.pop();
		while(m!=-1)
		{
			s.push(m);
			m=s1.pop();
		}
		for(int k=0;k<d;k++)
		{
		    if(data[vertex][k]!=0&&vis[k]==0)
		    {
		    	s.push(k);
		    	vis[k]=1;
		    	i++;
		    	break;
		    }
		}
    }
    cout<<"Depth First Traversal: ";
    m=s.pop();
    while(m!=-1)
    {
    	cout<<m+1<<" ";
    	m=s.pop();
    }
    return 0;
}
