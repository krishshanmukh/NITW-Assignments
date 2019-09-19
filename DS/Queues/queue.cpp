#include<iostream>
#include<cstring>
using namespace std;
class queue
{
	int size;
	char elts[50];
	int front;
	int rear;
	public:
		queue();
		int isqfull();
		queue(int a);
		int isqempty();
		void enqueue(int b);
		char delqueue();
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
char queue :: delqueue()
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
	cout<<"Enter parent class  : ";
	char ch;
	cin>>ch;
	enqueue(ch);
	enqueue('$');
	char choice;
	for(int k=0;k<=rear;k++)
	{
		int i,j;
		ch=elts[k];
		if(ch!='$')
		{
			cout<<"How many children does "<<ch<<" have? ";
		    cin>>i;
		    if(i>0)
		    cout<<"Enter children of "<<ch<<" :  "<<endl;
		    for(j=0;j<i;j++)
		    {
			    cin>>ch;
			    enqueue(ch);
		    }
		}
		else if(elts[rear]!='$')
		enqueue('$');
		else
		break;
	}
	enqueue('$');
}
void queue :: display()
{
	cout<<endl;
	for(int i=0;i<=rear;i++)
	{
		if(elts[i]!='$')
		cout<<elts[i]<<"  ";
		else 
		cout<<endl;
	}
}
int main()
{
	queue q;
	q.input();
	q.display();
	return 0;
}
