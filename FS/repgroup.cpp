#include <iostream>
#include <fstream>
#include <cstring>
#include<cstdlib>
using namespace std;
class student
{
	public:
		char rollno[7];
		char name[11];
		char cgpa[5];
		char blog[10];
		int no;
};
class buffer
{
	public:
	char buff[100];
    void pack(char a[]);
    void store(ofstream &out);
    void pack1 (char a[]);
};
void buffer :: pack1 (char a[])
{
	strcpy(buff,a);
	strcat(buff,"$");
}
void buffer :: pack (char a[])
{
	strcat(buff,a);
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
	buffer b;out.open("repgroup.txt");
	char ch='y';
	while(ch=='y')
	{
	    cout<<"Enter roll no:";
	    cin>>s.rollno;	b.pack1(s.rollno);
	    cout<<"Enter name:";
	    cin>>s.name;b.pack(s.name);
	    cout<<"Enter cgpa:";
	    cin>>s.cgpa;	b.pack(s.cgpa);
	    cout<<"Enter no. of backlogs : ";
	    cin>>s.no;
	    cout<<"Enter names of subject : ";
	    for (int i=0;i<s.no;i++)
	    {
	    	cin>>s.blog;
	    	b.pack(s.blog);
	    }
	    cout<<"Enter y to continue : ";
	    cin>>ch;b.store(out);
   	}
    out.close();
    return 0;
}
