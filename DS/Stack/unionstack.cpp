#include<iostream>
using namespace std;
union u
{
	int i;
	char ch;
	float f;
	char c[20];
};
class stack
{
	int top;
	union u elts[30];
	int size;	
	int tag[30];
    public :
		void push(u u1);
		u pop();
		void display();
		stack()
		{
			top=-1;
			size=0;
		}
		void input();
};
void stack :: input()
{
    cout<<"1. int\n2. char\n3. float\n4. string\n";
		cout<<"Enter choice : ";
		cin>>tag[size];
		if(tag[size]==1)
		{
			cin>>elts[size].i;
		}
		else if(tag[size]==2)
		{
			cin>>elts[size].ch;
		}
		else if(tag[size]==3)
		{
			cin>>elts[size].f;
		}
		else if(tag[size]==4)
		{
			cin>>elts[size].c;
		}
		else 
		{
		cout<<"Wrong input!";
		size--;
	    }
		size++;
}
u stack :: pop()
{
	if(size>=0)
	return elts[size--];
	else
	cout<<"Stack is empty";
}
void stack :: display ()
{
	for(int j=0;j<size;j++)
	{
		if(tag[j]==1)
		{
			cout<<elts[j].i<<" ";
		}
		else if(tag[j]==2)
		{
			cout<<elts[j].ch<<" ";
		}
		else if(tag[j]==3)
		{
			cout<<elts[j].f<<" ";
		}
		else
		{
			cout<<elts[j].c<<" ";
		}
	}
	cout<<endl;
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
		s.pop();
		else if(choice==3)
		s.display();
		else
		cout<<"Enter choice: ";
		cout<<"1. push\n2. pop\n3. display\n4. - exit\n";
		cin>>choice;
	}
	return 0;
}
