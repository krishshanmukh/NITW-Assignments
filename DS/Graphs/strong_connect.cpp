#include<iostream>
using namespace std;
int d,data[100][100],S[100],index[10],low[10],ind=1,in_stack[10];
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
stack s;

void strongconnect(int i)
{
	in_stack[i]=1;
	s.push(i);
	index[i]=ind;
	low[i]=ind++;
	for(int j=0;j<d;j++)
	{
		if(data[i][j]!=0)
		{
			if(index[j]==0)
			{
				strongconnect(j);
				low[i]=min(low[i],low[j]);
			}
			else if(in_stack[j]==1)
			low[i]=min(low[i],index[j]);
		}
	}
	cout<<i+1<<" "<<low[i]<<endl;
	if(low[i]==index[i])
	{
		int w=s.pop();
		cout<<"( ";
		while(w!=i)
		{
			in_stack[w]=0;
			cout<<w+1<<" ";
			w=s.pop();
		}
		cout<<i+1<<" )";in_stack[i]=0;
		cout<<endl;
		for(int j=0;j<d;j++)
		if(index[j]==0)
		strongconnect(j);
	}

}

int main()
{
	cin>>d;int a;
	for(int i=0;i<d;i++)
	{
		cout<<i+1<<" ";
		cin>>a;
		while(a!=-1)
		{
			data[i][a-1]=1;
			cin>>a;
		}
	}
	strongconnect(0);
}
