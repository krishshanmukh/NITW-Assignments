#include<iostream>
using namespace std;
class stack
{
	int elts[20];
	int elts1[20];
	int size;
	int top;
	int top1;
	public:
		stack()
		{
			size=20;
			top=-1;
			top1=-1;
		}
		stack(int x)
		{
			top=-1;
			top1=-1;
			size=x;
		}
		void push(int x);
		int pop();
		void push1(int x);
		int pop1();
		void sort();
		void input();
		void display();
};
void stack :: push (int x)
{
	if(top<size)
	elts[++top]=x;
	else
	cout<<"Stack is full";
}
int stack :: pop ()
{
	if(top>=0)
	return elts[top--];
	else
	return NULL;
}
void stack :: push1 (int x)
{
	if(top1<size)
	elts[++top1]=x;
	else
	cout<<"Stack is full";
}
int stack :: pop1 ()
{
	if(top1>=0)
	return elts[top1--];
	else
	return NULL;
}
void stack :: input()
{
	cout<<"Enter elements (0 to stop) : ";
	int c;
	cin>>c;
	while(c!=0)
	{
		push(c);
		cin>>c;
	}
}
void stack :: sort()
{
	int x,y,t,c=0,i,j;
	t=top;
	for(i=0;i<t;i++)
	{
		x=pop();
		y=pop();
		for(j=c;j<t;j++)
		{
			if(x>y)
			{
				push1(y);
				if(j!=t-1)
				y=pop();
				else
				push(x);
			}
			else
			{
				push1(x);
				if(j!=t-1)
				x=pop();
				else
				push(y);
			}
		}
		for(j=c;j<t;j++)
		{
			cout<<pop1()<"  ";
		}
		if(c==t)
		{
			if(x>y)
			{
				push(x);push(y);
			}
			else
			{
				push(y);push(x);
			}
		}
		c++;
		
	}
}
void stack :: display()
{
	while(top>=0)
	cout<<pop()<<" ";
}
int main()
{
	stack s;
	s.input();
	s.sort();
	s.display();
	return 0;
}
