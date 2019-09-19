#include<iostream>
#include<fstream>
using namespace std;
class stack
{
	int elt[10];
	int top;
	int spctr;
	public :
		stack()
		{
			spctr=0;
			top=-1;
		}
		void push(int a);
		int pop();
		void indent(ifstream &in,ofstream &out);
};
void stack :: push(int a)
{
	if(top<10)
	elt[++top]=a;
}
int stack :: pop()
{
	if(top>-1)
	return elt[top--];
}
void stack :: indent ()
{
	char ch;int i;
	in>>ch;
	int b[10];
	while(!in.eof())
	{
		if(ch==';')
		{
			out<<endl;
		    for(int i=0;i<spctr;i++)
        	out<<" ";
	    	out<<ch;
	    }
	    if(ch=='w')
	    {
	    	for(i=0;i<4;i++)
	    	{
	    		in>>ch;
	    		b[i]=ch;
	    	}
	    	b[i]='/0';
	    	if(b=="while")
	    	{
	    		out<<"hile";
	    		push(3);
	    		in>>ch;
	    		while(ch!=')')
	    		{
	    			out<<ch;
	    		}
	    		if(ch=='{')
	    		{
	    			for(i=0;i<spctr;i++)
	    		    out<<" ";
	    		    out<<ch;
	    		    spctr+=3;
	    		}
	    	} 
			if(ch=='f')
	    {
	    	for(i=0;i<2;i++)
	    	{
	    		in>>ch;
	    		b[i]=ch;
	    	}
	    	b[i]='/0';
	    	if(b=="while")
	    	{
	    		out<<"hile";
	    		push(3);
	    		in>>ch;
	    		while(ch!=')')
	    		{
	    			out<<ch;
	    		}
	    		if(ch=='{')
	    		{
	    			for(i=0;i<spctr;i++)
	    		    out<<" ";
	    		    out<<ch;
	    		    spctr+=3;
	    		}
	    	}   
	    }
	    
	}
}
