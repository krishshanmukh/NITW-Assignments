#include<iostream>
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
	queue q;
	cout<<"Enter no. of vertices: ";
	cin>>v;
	const int d=v;
	int data[d][d],dis[d],vis[d],cur,vertex,count,i=0;
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
	q.enqueue(cur);
	i++;
	vis[cur]=1;
	while(i!=d)
	{
		cout<<i;
		vertex=q.delqueue();
		while(!check(data[vertex],d))
		{
			q.enqueue(vertex);
			vertex=q.delqueue();
		}
		q.enqueue(vertex);
		for(int k=0;k<d;k++)
		{
		    if(data[vertex][k]!=0&&vis[k]==0)
		    {
		    	q.enqueue(k);
		    	vis[k]=1;
		    	i++;
		    }
		}
	}
	cout<<"Breadth First Traversal is: \n";
	int m=q.delqueue();
	while(m!=cur)
	{
		q.enqueue(m);
		m=q.delqueue();
	}
	cout<<m+1<<" ";
	while(!q.isqempty())
	{
		cout<<q.delqueue()+1<<" ";
	}
	return 0;
}
