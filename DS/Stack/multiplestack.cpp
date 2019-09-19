#include <iostream>
using namespace std;
class stack
{
	int top[10];
	int elts[100];
	int n;
	public:
		stack(int a)
		{
			n=a;int i=0;
			top[i]=-1;
			for(int j=100/n;j<100;j=100*(i+1)/n)
			{
				top[i+1]=j-1;
				i++;
			}
		}
		void push(int x,int i);
		int pop(int i);
		void display(int i);
		void input(int i);
};
void stack :: push(int x,int i)
{
	if((top[i-1])<i*100/n)
	elts[++top[i-1]]=x;
	else
	cout<<"Stack is full";
}
int stack :: pop(int i)
{
	if(top[i-1]>=(i-1)*100/n)
	return elts[top[i-1]--];
	else
	cout<<"Stack is empty";
}
void stack :: display(int i)
{
	for(int j=(i-1)*100/n;j<=top[i-1];j++)
	cout<<elts[j]<<" ";
}
void stack :: input(int i)
{
	int x;
	cout<<"Enter element of stack : ";
	cin>>x;
	push(x,i);
}
int main()
{
	stack s(5);
	int choice,i;
	cout<<"1. push\n2. pop\n3. display\n4. - exit\n";
	cout<<"choice : ";
	cin>>choice;
	while(choice!=4)
	{
		if(choice==1)
		{cout<<"Enter stack no: ";cin>>i;
		s.input(i);}
		else if(choice==2)
		{cout<<"Enter stack no: ";cin>>i;
		s.pop(i);}
		else if(choice==3)
		{cout<<"Enter stack no: ";cin>>i;
		s.display(i);}
		else;
		cout<<"1. push\n2. pop\n3. display\n4. - exit\n";
		cout<<"Enter choice: ";
		cin>>choice;
	}
	return 0;
}
