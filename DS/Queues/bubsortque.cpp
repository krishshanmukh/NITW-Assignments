#include<iostream>
#include<cstring>
using namespace std;
class queue
{
	int size;
	int elts[50];
	int front;
	int rear;
	public:
		queue();
		int isqfull();
		queue(int a);
		int isqempty();
		void enqueue(int b);
		int delqueue();
		void input();
		void display();
		void sort();
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
void queue :: display()
{
	cout<<endl;
	for(int i=front;i<=rear;i++)
	{
		cout<<elts[i]<<"  ";
	}
}
void queue :: input()
{
	cout<<"Enter elements of queue : (0 to stop)";
	int c;
	cin>>c;
	while(c!=0)
	{
		enqueue(c);
		cin>>c;
	}
}
void queue :: sort()
{
	int i,r,a,b,j;
	int c=rear;
	for(j=0;j<c;j++)
	{
		i=front;
		r=rear;
		a=delqueue();
		b=delqueue();
		for(i;i<r;i++)
		{
			if(i<r-j)
			{
				if(a>b)
			    {
				    enqueue(b);
				    if(i!=r-j-1)
				    b=delqueue();
				    else
				    enqueue(a);
			    }
			    else
			    {
				    enqueue(a);
				    if(i!=r-j-1)
				    a=delqueue();
				    else
				    enqueue(b);
			    }
			}
			else
			{
				for(int k=r-j;k<r;k++)
		        {
			        a=delqueue();
			        enqueue(a);
		        }break;
			}
		}
	}
}
int main()
{
	queue q;
	q.input();
	q.sort();
	q.display();
	return 0;
}
