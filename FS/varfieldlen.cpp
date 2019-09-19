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
	char ch;int i=0;//in>>ch;
	//while(ch!='$')
//	{
//		s.rollno[i]=ch;
//		i++;
//		in>>ch;
//	}
//    s.rollno[i]='\0';
//	i=0;in>>ch;
in.getline(s.rollno,7,'$');//in>>ch;
//	while(ch!='$')
//	{
//		s.name[i]=ch;
//		i++;
//		in>>ch;
//	}
//	s.name[i]='\0';
in.getline(s.name,10,'$');
    //i=0;in>>ch;
//	while(ch!='$')
//	{
//		s.cgpa[i]=ch;
//		i++;
//		in>>ch;
//	}
//	s.cgpa[i]='\0';
	in.getline(s.cgpa,5,'$');
	return in;
}
int main()
{
	ofstream out;
	student s;
	buffer b;out.open("varfieldlength.txt");
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
    in>>s;
    char c[20];
    cout<<"Enter name to search : ";
    cin>>c;int a;
    while(!in.eof())
    {
    	a=strcmp(s.name,c);cout<<s.name;
    	if(a==0)
    	{
    		cout<<"Roll no : "<<s.rollno<<" Name : "<<s.name<<" cgpa : "<<s.cgpa ;
    		break;
    	}
    	else
    	in>>s;
    }
}
