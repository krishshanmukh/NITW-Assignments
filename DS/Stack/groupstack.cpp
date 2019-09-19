#include<iostream>
using namespace std;
class stack
{
	int top;
	int top1;
	int elts[30];
	int ctr[5];
	public:
		stack()
		{
			top=top1=-1;
		}
		void push(int i);
		int pop();
		void POP();
		void push1(int i);
		int pop1();
		void display();
		void input();
};
void stack :: push(int i)
{
	if(top<30)
	elts[++top]=i;
	else
	cout<<"Stack is full!";
}
int stack :: pop()
{
	if(top>=0)
	return elts[top--];
	else
	cout<<"Stack is empty!";
}
int stack :: pop1()
{
	if(top1>=0)
	return ctr[top1--];
	else
	cout<<"Stack is empty!";
}
void stack :: POP()
{
	if(top<=-1)
	{
		cout<<"stack is empty";
		return ;
	}
	int c=pop1();
	for(int i=0;i<c;i++)
	pop();
}
void stack :: push1(int i)
{
	if(top1<30)
	ctr[++top1]=i;
	else
	cout<<"Stack is full!";
}
void stack :: input()
{
	int t;
	cout<<"Enter no. of elts in group: ";
	cin>>t;
	push1(t);
	for(int i=0;i<t;i++)
	{
		int j;
		cin>>j;
		push(j);
	}
}
void stack :: display()
{
	int k=0;
	int l=ctr[0];
	for(int j=0;j<=top1;j++)
	{
	    for(int i=k;i<l;i++)
	    cout<<elts[i]<<" ";
	    cout<<"\t";
	    k+=ctr[j];
	    l+=ctr[j+1];
	}
}
int main()
{
	stack s;
	int choice;
	cout<<"1. push\n2. pop\n3. display\n4. - exit\n";
	cout<<"choice : ";
	cin>>choice;
	while(choice!=4)
	{
		if(choice==1)
		s.input();
		else if(choice==2)
		s.POP();
		else if(choice==3)
		s.display();
		else
		cout<<"Enter choice: ";
		cout<<"1. push\n2. pop\n3. display\n4. - exit\n";
		cin>>choice;
	}
	return 0;
}
