#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class student
{
	public:
		char rollno[7];
		char name[11];
		char cgpa[5];
};
class buffer
{
	public:
	char buff[30];
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
	while(ch!='$')
	{
		s.cgpa[i]=ch;
		i++;
		in>>ch;
	}
	s.cgpa[i]='\0';
	return in;
}
int main()
{
	ofstream out;
	student s;
	buffer b;out.open("varfieldlength.txt", ios :: app);
	char ch='y';
	while(ch=='y')
	{
	    cout<<"Enter roll no:";
	    cin>>s.rollno;	b.pack1(s.rollno);
	    cout<<"Enter name:";
	    cin>>s.name;b.pack(s.name);
	    cout<<"Enter cgpa:";
	    cin>>s.cgpa;	b.pack(s.cgpa);
	    cout<<"Enter y to continue : ";
	    cin>>ch;b.store(out);
   	}
    out.close();
    ifstream in("varfieldlength.txt");
    student S[100];
    int i=0,a;
    while(!in.eof())
    {
    	in>>S[i];
    	i++;
    }
    for(int j=0;j<i-1;j++)
    {
    	for(int k=0;k<i-j-1;k++)
    	{
    		a=strcmp(S[k].cgpa,S[k+1].cgpa);
    		if(a==-1)
    		{
    			student K;
    			K=S[k];
    			S[k]=S[k+1];
    			S[k+1]=K;
    		}
    	}
    }
    out.open("sort.txt");
    for(int j=0;j<i-1;j++)
    {
    	b.pack1(S[j].rollno);
	    b.pack(S[j].name);
	    b.pack(S[j].cgpa);
	    cout<<S[j].cgpa<<" "<<S[j].rollno<<" "<<S[j].name<<"\n";
	    b.store(out);
    }
    out.close();
    return 0;
}
