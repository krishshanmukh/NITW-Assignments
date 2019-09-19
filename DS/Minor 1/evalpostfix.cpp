#include<iostream>
using namespace std;

class queue1
{
	int size;
	char elts[50];
	int front;
	int rear;
	public:
		queue1();
		int isqfull();
		int isqempty();
		void enqueue(char b);
		char delqueue();
		void input();
		void display();
};
queue1 :: queue1()
{
	size=50;
	front=-1;
	rear=-1;
}

class queue2
{
	int size;
	int elts[50];
	int front;
	int rear;
	public:
		queue2();
		int isqfull();
		int isqempty();
		void enqueue(int b);
		int delqueue();
		void input();
		void display();
};
queue2 :: queue2()
{
	size=50;
	front=-1;
	rear=-1;
}

void queue1 :: enqueue (char b)
{
		rear=(rear+1)%size;
		elts[rear]=b;
		if(front==-1)
		front ++;
}
char queue1 :: delqueue()
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
int queue1 :: isqfull()
{
	if(((rear+1)%size)==front)
	return 1;
	else return 0;
}
int queue1 :: isqempty()
{
	if(front==-1)
	return 1;
	else return 0;
}

void queue2 :: enqueue (int b)
{
		rear=(rear+1)%size;
		elts[rear]=b;
		if(front==-1)
		front ++;
}
int queue2 :: delqueue()
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
int queue2 :: isqfull()
{
	if(((rear+1)%size)==front)
	return 1;
	else return 0;
}
int queue2 :: isqempty()
{
	if(front==-1)
	return 1;
	else return 0;
}

int eval(char op,int a,int b)
{
	if(op=='*')
	return a*b;
	else if(op=='/')
	return a/b;
	else if(op=='-')
	return a-b;
	else
	return a+b;
}

int evaluate(queue1 q1, queue2 q2)
{
	char a=q1.delqueue();int c=0;
	int x,y;
	while(!q1.isqempty()||c==0)
	{
		c=1;
		x=q2.delqueue();
		y=q2.delqueue();
		q2.enqueue(eval(a,x,y));
		a=q1.delqueue();
	}
	return q2.delqueue();
}

int main()
{
	char ch[50];
	queue1 q1;queue2 q2;
	cout<<"Enter the postfix expression: ";
	cin.getline(ch,50,'\n');
	int i=0;
	while(ch[i]!='\0')
	{
		if(ch[i]!='+'&&ch[i]!='/'&&ch[i]!='*'&&ch[i]!='-')
		{
			int b=0;
			while(ch[i]!=' ')//to store integers greater than 10
			{
				b=b*10+(ch[i]-'0');
				i++;
			}
			q2.enqueue(b);cout<<b;
		}
		else
		{cout<<ch[i];
			q1.enqueue(ch[i]);i++;
		}
		while(ch[i]==' ')//to remove white spaces
		i++;
	}
	cout<<"Answer is "<<evaluate(q1,q2);
}
