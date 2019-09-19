#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
union u
{
	char mob[11];
	char land[9];
};
class student
{
	public:
		char rollno[7];
		char name[15];
		int tag;
		u u1;
};
class buffer
{
	public:
	char buff[40];
    void pack1(char a[]);
    void pack(char a[]);
    void store(ofstream &out);
};
ifstream & operator >> (ifstream & in,student &s)
{
	char ch;int i=0;in>>ch;
	while(ch!='$')
	{
		s.rollno[i]=ch;
		i++;
		in>>ch;
	}
    s.rollno[i]='\0';
	i=0;in>>ch;
	while(ch!='$')
	{
		s.name[i]=ch;
		i++;
		in>>ch;
	}
	s.name[i]='\0';
    i=0;in>>ch;
    s.tag=ch-'0';
	if(s.tag==1)
	{i=0;in>>ch>>ch;
		while(ch!='$')
	{
		s.u1.mob[i]=ch;
		i++;
		in>>ch;
	}
	s.u1.mob[i]='\0';
	}
	else
	{
	    i=0;in>>ch>>ch;
		while(ch!='$')
	{
		s.u1.land[i]=ch;
		i++;
		in>>ch;
	}
	s.u1.land[i]='\0';
	
	}
}
ofstream & operator << (ofstream &out, student &s)
{
	out<<s.rollno;
	out<<s.name;
	if(s.tag==1)
    cout<<s.u1.mob;
    else
    cout<<s.u1.land;
	return out;
}
void buffer :: pack (char a[])
{
	strcat(buff,a);
	strcat(buff,"$");
}
void buffer :: pack1 (char a[])
{
	strcpy(buff,a);
	strcat(buff,"$");
}
void buffer :: store (ofstream &out)
{
	int l;
	l = strlen(buff);
    for(int i=0;i<l;i++)
    out<<buff[i];
}
int main()
{
	ofstream out;
	student s;
	buffer b;out.open("buffer1.txt");
	char choice='y';
	while(choice=='y')
	{
	cout<<"Enter roll no:";
	cin>>s.rollno;	b.pack1(s.rollno);
	cout<<"Enter name:";
	cin>>s.name;b.pack(s.name);
	cout<<"1.mobile no\n2.landline no";
	cin>>s.tag;
	if(s.tag==1)
	{
		b.pack("1");
	    cin>>s.u1.mob;	b.pack(s.u1.mob);
	}
	if(s.tag==2)
	{
		b.pack("2");
	    cin>>s.u1.land;	b.pack(s.u1.land);
	}
	b.store(out);
	cout<<"Enter y to continue: ";
	cin>>choice;}
	out.close();
    ifstream in("buffer1.txt");
    in>>s;
    char c[20];
    cout<<"Enter name to search : ";
    cin>>c;int a;
    while(!in.eof())
    {
    	a=strcmp(s.name,c);
    	if(a==0)
    	{
    		cout<<"Roll no : "<<s.rollno<<" Name : "<<s.name;
    		if(s.tag==1)
    		cout<<" Mobile: "<<s.u1.mob;
    		else
    		cout<<" Landline : "<<s.u1.land;
    		break;
    	}
    	else
    	in>>s;
    }	
	return 0;
}
