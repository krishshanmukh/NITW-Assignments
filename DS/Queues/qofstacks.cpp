#include<iostream>
#include<cstdlib>
using namespace std;
class stack
{
	int element[6];
	int top;
	public :
		int s;
		stack()
		{
			top=-1;
		}
		void push(int i);
		int pop();
};
class queue
{
	int size;
	stack elts[20];
	int front;
	int rear;
	public:
		queue();
		int isqfull();
		queue(int a);
		int isqempty();
		void enqueue(int x);
		void delqueue();
		void input();
		void display();
};

int stack :: pop()
{
	if(top>-1)
	return (element[top--]);
	else
	return NULL;
}
void stack :: push(int i)
{
	if(top<30)
	element[++top]=i;
	else
	cout<<"Stack is full!";
}
queue :: queue()
{
	size=20;
	front=-1;
	rear=-1;
}
queue :: queue(int a)
{
	size=a;
	front=-1;
	rear=-1;
}
void queue :: enqueue (int x)
{
	if(isqfull())
	cout<<"Q is full";
	else
	{
		int c;
		elts[rear+1].s=x;
		if(front==-1)
		front++;
		rear=(rear+1)%size;
		for(int i=0;i<x;i++)
		{cin>>c;
		elts[rear].push(c);}
		if(front==-1)
		front ++;
	}
}
void queue :: delqueue()
{
	if(isqempty())
	cout<<"Empty!";
	else
	{
		for(int i=0;i<elts[front].s;i++)
		cout<<elts[front].pop()<<" ";
		if(front==rear)
		front=rear=-1;
		else
		front=((front+1)%size);
	}
}
int queue :: isqfull()
{
	if(((rear+1)%size)==front)
	return 1;
	else return 0;
}
int queue :: isqempty()
{
	if(front==-1)
	return 1;
	else return 0;
}
void queue :: display()
{
	int r=rear;
	for(int i=front;i<=r;i++)
	{
		for(int j=0;j<elts[i].s;j++)
		cout<<elts[i].pop()<<" ";
		cout<<endl;
	}
}
void queue :: input()
{
	cout<<"Enter size of stack : ";
	cin>>elts[rear+1].s;
	enqueue(elts[rear+1].s);
}
int main()
{
	queue q;
	cout<<"\n1.Enqueue\n2.Delque\n3.Display\nother.exit\n";
	cout<<"Enter choice: ";
	int ch;
	cin>>ch;
	l1: switch(ch)
	{
		case 1:cout<<"Enter size: ";int size;cin>>size;q.enqueue(size);break;
		case 2:q.delqueue();break;
		case 3:q.display();break;
		default: exit(0);
	}
	cout<<"Enter choice: ";
	cin>>ch;
	if(ch==1||ch==2||ch==3||ch==4)
	goto l1;
	return 0;
}
