#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
union u
{
	char mob[11];
	char land[8];
};
class student
{
	public:
		char rollno[7];
		char name[11];
		char tag;
		u u1;
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
    in>>s.tag;in>>ch;
    if(s.tag=='1')
    {
    i=0;in>>ch;
	while(ch!='$')
	{
		s.u1.mob[i]=ch;
		i++;
		in>>ch;
	}
	s.u1.mob[i]='\0';} else{
	i=0;in>>ch;
	while(ch!='$')
	{
		s.u1.land[i]=ch;
		i++;
		in>>ch;
	}
    s.u1.land[i]='\0';}
	return in;
}
ofstream & operator << (ofstream &out, student &s)
{
	out<<s.rollno<<" ";
	out<<s.name<<" ";
	out<<s.tag<<" ";
	if(s.tag=='1')
	out<<s.u1.mob;
	if(s.tag=='2')
	out<<s.u1.land;	
	return out;
}
int main()
{
	ifstream in("stud.txt");
	ofstream out;
	student s;
	in>>s;
    out.open("buffer11.txt");
	out<<s;
	out.close();	
	return 0;
}
