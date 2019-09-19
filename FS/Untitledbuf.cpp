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
		char name[11];
		char tag;
		u u1;
};
ifstream & operator >> (ifstream & in,student &s)
{
	char a[15];int i=0;in>>a[i];
	while(a[i]!='$')
	{
		i++;
		in>>a[i];
	}
	for(int j=0;j<i;j++)
	s.rollno[j]=a[j];s.rollno[i]='\0';
	i=0;in>>a[i];
	while(a[i]!='$')
	{
		i++;
		in>>a[i];
	}
	for(int j=0;j<i;j++)
	s.name[j]=a[j];s.name[i]='\0';
    in>>s.tag;
    if(s.tag=='1')
    i=0;in>>a[i];
	while(a[i]!='$')
	{
		i++;
		in>>a[i];
	}
	for(int j=0;j<i;j++)
	s.u1.mob[j]=a[j];s.u1.mob[i]='\0';i=0;in>>a[i];
	while(a[i]!='$')
	{
		i++;
		in>>a[i];
	}
	for(int j=0;j<i;j++)
	s.u1.land[j]=a[j];s.u1.land[i]='\0';
	return in;
}
ofstream & operator << (ofstream &out, student &s)
{
	out<<s.rollno;
	out<<s.name;
	out<<s.tag;
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
