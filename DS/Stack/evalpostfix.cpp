#include<iostream>
#include<cstdlib>
using namespace std;
class stack
{
	int elts[20];
	char a[20];
	int size;
	int top;
	int res;
	char ch[1];
	public:
		stack()
		{
			size=20;
			top=-1;
		}
		stack(int x)
		{
			top=-1;
			size=x;
		}
		void push(int x);
		int pop();
		int result();
		void input();
};
void stack :: push (int x)
{
	if(top<size)
	elts[++top]=x;
	else
	cout<<"Stack is full";
}
int stack :: pop ()
{
	if(top>=0)
	return elts[top--];
	else
	cout<<"Stack is empty";
}
int stack :: result ()
{
	int i=0;
	while(a[i]!='\0')
	{
		if((a[i]!='-')&&(a[i]!='+')&&(a[i]!='*')&&(a[i]!='/'))
		{
			int x;ch[0]=a[i];
			x=atoi(ch);cout<<x;
			push(x);
		}
		else
		{int c=pop();int b=pop();
			switch(a[i])
			{
				case '-': res=b-c;push(res);cout<<res;
				break;
				case '+': res=c+b;push(res);cout<<res;
				break;
				case '*': res=c*b;push(res);cout<<res;
				break;
				case '/': res=b/c;push(res);cout<<res;
				break;
			}
		}
		i++;
	}
	return res;
}
void stack :: input()
{
	cout<<"Enter expression: ";
	cin>>a;
}
int main()
{
	stack s;
	s.input();
	cout<<"\nAnswer is : "<<s.result();
	return 0;
}
