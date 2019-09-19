#include <iostream>
using namespace std;
class stack
{
	int top1,top2;
	int elts[40];
	public:
		stack()
		{
			top1=-1;
			top2=40;
		}
		void push1(int x);
		int pop1();
		void push2(int x);
		int pop2();
		void display1();
		void display2();
};
void stack :: push1(int x)
{
	if(top1<top2-1)
	elts[++top1]=x;
	else
	cout<<"Stack is full";
}
void stack :: push2(int x)
{
	if(top2>top1+1)
	elts[--top2]=x;
	else
	cout<<"Stack is full";
}
int stack :: pop1()
{
	if(top1>=0)
	return elts[top1--];
	else
	cout<<"Stack is empty";
}
int stack :: pop2()
{
	if(top2<40)
	return elts[top2++];
	else
	cout<<"Stack is empty";
}
void stack :: display1()
{
	for(int i=0;i<=top1;i++)
	cout<<elts[i]<<" ";
}
void stack :: display2()
{
	for(int i=39;i>=top2;i--)
	cout<<elts[i]<<" ";
}
int main()
{
	stack s;
	int choice;
	cout<<"1. push (stack1)\n2. pop(stack1)\n3. display(stack1)\n4.push(stack2)\n5.pop (stack2)\n6.display(stack2)\n7. exit";
	cout<<"choice : ";
	cin>>choice;
	while(choice!=7)
	{
		if(choice==1)
		{
			int n;
			cout<<"Enter no. ";
			cin>>n;
			s.push1(n);
		}
		else if(choice==2)
		s.pop1();
		else if(choice==3)
		s.display1();
		else if(choice==4)
		{
			int n;
			cout<<"Enter no. ";
			cin>>n;
			s.push2(n);
		}
		else if(choice==5)
		s.pop2();
		else if(choice==6)
		s.display2();
		else;
		cout<<"Enter choice: ";
		cin>>choice;
	}
	return 0;
}
