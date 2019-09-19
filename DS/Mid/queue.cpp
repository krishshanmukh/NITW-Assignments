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
		void enqueue1(queue q,int b);
		int delqueue();
		void delqueue1(queue q);
		void input();
		void display(queue q);
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

void queue :: enqueue1 (queue q,int b)
{
	if(isqfull())
	cout<<"Q is full";
	else
	{
		int c;
		cout<<"Enter elts: ";
		q.enqueue(b);
	    for(int i=0;i<b;i++)
	    {
	    	cin>>c;
	    	enqueue(c);
	    }
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

void queue :: delqueue1(queue q)
{
	if(q.isqempty())
	return ;
	else
	{
		for(int i=0;i<q.delqueue();i++)
		cout<<delqueue();
	}
}

void queue :: display(queue q)
{
	cout<<endl;
	int c=0,d=0,i=front;
	while(i!=rear)
	{
	    c=q.delqueue();
	    d+=c;
	    for(int j=i;i<c;i=(i+1)%size)
	    {
	        cout<<elts[i]<<" ";
	    }
	    q.enqueue(c);
	}
}
int main()
{
	queue q,q1;
	char ch;
	int n,c;
	do
	{
		cout<<"Enter no. of elts: ";
		cin>>n;
		q.enqueue1(q1,n);
		cout<<"y to continue: ";
		cin>>ch;
	}while(ch=='y');
	q.delqueue1(q1);
	cout<<endl;
	q.display(q1);
	return 0;
}
