#include<iostream>
#include<cstring>
using namespace std;
class stack
{
	char c[30];
	int top;
	int size;
	char a[15];
	char sym[6];
	public:
		stack()
		{
			top=-1;
			sym[0]='+';sym[1]='-';sym[2]='*';sym[3]='/';sym[4]='(';sym[5]=')';
		}
		void input();
		void push(char ch);
		char pop();
		void convert();
		void output();
};
void stack :: input()
{
	cout<<"Enter the expression : ";
	cin>>c;
	size=strlen(c);
}
void stack :: push (char ch)
{
	a[++top]=ch;
}
char stack :: pop ()
{
	return a[top--];
}
void stack :: convert ()
{
	int i=0,j,m,n;
	for(j=0;j<size;j++)
	{ m=1;
		for(int k=0;k<6;k++)
		{
			if(c[j]==sym[k])
		{   m=0;
			if(top==-1)
			{
				push(c[j]);break;
			}
			else if(k==4)
			{
				push(c[j]);n=top;
			}
			else if(k==5)
			{
				for(static int l=top;l>=n;l--)
				{
					if(l==n)
					pop();
					else
					cout<<pop();
				}
			}
			else
			{
				if((k==3||k==2)&&((a[top]=='+'||a[top]=='-')||a[top]=='(')))
				{
				push(c[j]);}
				else
				{
					cout<<pop();
					while(a[top]=='+'||a[top]=='-')
                cout<<pop();
				push(c[j]);
				}
			}break;
		}
	    }
	    if(m==1)
	    cout<<c[j];
	}
	while(top>=0)
        cout<<pop();
}
int main()
{
	stack s;
	s.input();
	s.convert();
	return 0;
}
