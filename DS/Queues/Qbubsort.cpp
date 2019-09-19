#include<iostream>
#include<cstring>
using namespace std;
class queue
{
	int size;
	int elts[20];
	int front;
	int rear;
	public:
		queue();
		int isqfull();
		void sort (queue &q2);
		queue(int a);
		int isqempty();
		void enqueue(int b);
		int delqueue();
		void input();
		void display();
};
queue :: queue()
{
	size=50;
	front=-1;
	rear=-1;
}
queue :: queue(int a)
{
	size=a;
	front=-1;
	rear=-1;
}
void queue :: enqueue (int b)
{
	if(isqfull())
	cout<<"Q is full";
	else
	{
		rear=(rear+1)%size;
		elts[rear]=b;
		if(front==-1)
		front ++;
	}
}
int queue :: delqueue()
{
	if(isqempty())
	return NULL;
	else
	{
		int c=elts[front];
		if(front==rear)
		front=rear=-1;
		else
		front=((front+1)%size);
		return c;
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
void queue :: input()
{
	cout<<"Enter no. of elements : ";
	int n;
	cin>>n;
	cout<<"Enter the elements : ";
    for(int i=0;i<n;i++)
    {
    	int x;
    	cin>>x;
    	enqueue(x);
    }
}
void queue :: sort (queue &q2)
{
	int a=rear;
	for(static int k=front;k<a-1;k++)
	{
		int d=rear;
		int b=delqueue();
		int c=delqueue();
		for(static int i=front;i<d-1;i++)
		{
			if(b>c)
			{
				if(i!=d-2)
				{
				enqueue(c);
				c=delqueue();}
				else
				q2.enqueue(b);
			}
			else
			{
				if(i!=d-2)
				{
				enqueue(b);
				b=delqueue();}
				else
				q2.enqueue(c);
			}
		}
	}
}
void queue :: display()
{
	int c=rear;
	for(static int i=front;i<c;i++)
	cout<<delqueue();
}
int main()
{
	queue q1,q2;
	q1.input();
	q1.sort(q2);
	q2.display();
	return 0;
}
