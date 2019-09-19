#include<iostream>
#include<fstream>
using namespace std;
class stack
{
	int elt[15];
	int spctr;
	int top;
	public :
		stack()
		{
			top=-1;
			spctr=0;
		}
		int pop();
		void push(int i);
		void indent(ifstream &in, ofstream &out);
};
void stack :: push(int i)
{
	if(top<15)
	elt[++top]=i;
	else
	cout<<"Stack is full!";
}
int stack :: pop()
{
	if(top>=0)
	return elt[top--];
	else
	cout<<"Stack is empty!";
}
void stack :: indent(ifstream &in, ofstream &out)
{
	char ch;
	in>>(ch);
	while(!in.eof())
	{
			if(ch=='#')
		{
	        out<<ch<<" ";
	        in.get(ch);
	        while(ch!='>')
	        {
	        out<<ch;in.get(ch);}
	        out<<ch<<"\n";
	    }
	else if(ch==';')
    {
	    out<<ch<<"\n";
	    for(int i=0;i<spctr;i++)
		out<<" ";
    }
	else if(ch=='{')
	{
	    out<<"\n\n";
	    for(int i=0;i<spctr;i++)
		out<<" ";
		out<<ch<<"\n";
		spctr+=3;
		push(3);
        for(int i=0;i<spctr;i++)
		out<<" ";
	}
	else if(ch=='}')
	{
		spctr-=pop();
		out<<"\n";
		for(int i=0;i<spctr;i++)
		out<<" ";
		out<<ch<<"\n";
		for(int i=0;i<spctr;i++)
		out<<" ";
	}
	else if(ch=='(')
	{
		while(ch!=')')
		{
			out<<ch;
			in.get(ch);
		}
		out<<ch<<"\n";
	}
	else
	{
		out<<ch;
	}in.get(ch);
	}
}
int main()
{
	ifstream in("input.txt");
	ofstream out("indentation.txt");
	stack s;
	s.indent(in,out);
	return 0;
}
