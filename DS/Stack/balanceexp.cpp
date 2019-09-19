#include <iostream>
#include <cstring>
using namespace std;
class stack
{
	char element[6];
	int top;
	int n=1;
	int size;
	char c[30];
	char osym[3];
	char csym[3];
	public :
		stack()
		{
			top=-1;
		}
		void input();
		void verify();
		void push();
		char pop();
};
void stack :: input()
{
	osym[0]='(';
	osym[1]='{';
	osym[2]=']';
	csym[0]=')';
	csym[1]='}';
	csym[2]=']';
	cout<<"Enter expression: "<<endl;
	cin>>c;
}
void stack :: push()
{
	size = strlen(c);
	for(int i=0;i<size;i++)
	{
		if(c[i]==osym[0]||c[i]==osym[1]||c[i]==osym[2])
		element[++top]=c[i];
	}
}
char stack :: pop()
{
	if(top>-1)
	return (element[top--]);
	else
	return NULL;
}
void stack :: verify()
{
	for(int i=0;i<size;i++)
	{
	    if(c[i]==csym[0])
		{
			if(osym[0]!=pop())
		    n=0;
		}
		if(c[i]==csym[1])
		{
			if(osym[1]!=pop())
			n=0;
		}
		if(c[i]==csym[2])
		{
			if(osym[2]!=pop())
			n=0;
		}
	}
	if(top!=-1)
    n=0;
	if(n==0)
	cout<<"Expression is not balanced !";
	else
	cout<<"Expression is balanced !";
}
int main()
{
	stack s;
	s.input();
	s.push();
	s.verify();
	return 0;
}

