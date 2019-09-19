#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream o1,o2;
	int a,b;
	char ch='y';
	o1.open("d1.txt");
	o2.open("d2.txt");
	cout<<"Enter the elements of file 1(in sorted order): ";
	while(ch=='y')
	{
		cin>>a;
		o1<<a<<" ";
		cout<<"Do you wish to enter more elements?(y for yes): ";
		cin>>ch;
	}
	ch='y';
	cout<<"Enter the elements of file 2(in sorted order): ";
	while(ch=='y')
	{
		cin>>a;
		o2<<a<<" ";
		cout<<"Do you wish to enter more elements?(y for yes): ";
		cin>>ch;
	}
	o1.close();
	o2.close();
	ifstream i1,i2;
ofstream o;
i1.open("d1.txt");
i2.open("d2.txt");
o.open("sort.txt");
i1>>a;
i2>>b;
while(!i1.eof()&&!i2.eof())
{
	if(a>b)
	{
		o<<b<<" ";
		i2>>b;
	}
	else
	{
		o<<a<<" ";
		i1>>a;
	}
}
while(!i1.eof())
{
	o<<a<<" ";
	i1>>a;
}
while(!i2.eof())
{
	o<<b<<" ";
	i2>>b;
}
o.close();
i1.close();
i2.close();
return 0;
}


	
