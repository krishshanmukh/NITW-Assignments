#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;

struct multi_node
{
	int sfptr;
	int sbptr;
	char rollno[7];
	int cfptr;
	int cbptr;
	char course[4];
};

struct student
{
	int rno;
	char rollno[7];
	char name[10];
	char cgpa[5];
};

struct course
{
	int rno;
	char cname[10];
	char cnumber[4];
};

ifstream & operator >> (ifstream &f, student &s)
{
	f.getline(s.rollno,10,' ');
	s.rno=atoi(s.rollno);
	f.getline(s.rollno,7,' ');
	f.getline(s.name,10,' ');
	f.getline(s.cgpa,5,'\n');
}

ofstream & operator << (ofstream &f, student &s)
{
	f<<s.rno++<<" "<<s.rollno<<" "<<s.name<<" "<<s.cgpa<<endl;
}

ifstream & operator >> (ifstream &f,course &c)
{
	f.getline(c.cnumber,4,' ');
	c.rno=atoi(c.cnumber);
	f.getline(c.cnumber,4,' ');
	f.getline(c.cname,10,'\n');
}

int main()
{
	ofstream out1("studentdata.txt"),out2("coursedata.txt");
	//out1.close();out2.close();
	ifstream f1("studentdata.txt"),f2("coursedata.txt");
	int choice=1;
	student s,S;
	course c,C;
	s.rno=0;c.rno=0; int x,scur=-1,ccur=-1;
	while(choice)
	{
		cout<<"Enter rollno: ";
		cin>>s.rollno;
		f1.seekg(0,ios::beg);
		f1>>S;
		while(!f1.eof())
		{
			x=strcmp(S.rollno,s.rollno);
			if(x==0)
			break;cout<<S.rollno<<" ";
			f1>>S;
		}
		if(x!=0)
		{
			f1.seekg(0,ios::end);
			cout<<"Enter name: ";
			cin>>s.name;
			cout<<"Enter cgpa: ";
			cin>>s.cgpa;
			//f1<<s.rno++<<" "<<s.rollno<<" "<<s.name<< " "<<s.cgpa<<endl;
			out1<<s;
			scur=out1.tellp();
		}
		cout<<"Enter course no: ";
		cin>>c.cnumber;
		f2.seekg(0,ios::beg);
		f2>>C;
		while(!f2.eof())
		{
			x=strcmp(C.cnumber,c.cnumber);
			if(x==0)
			break;
			f2>>C;
		}
		if(x!=0)
		{
			f2.seekg(0,ios::end);
			cout<<"Enter course name: ";
			cin>>c.cname;
			out2<<c.rno++<<" "<<c.cnumber<<" "<<c.cname<<endl;
			ccur=out2.tellp();
		}
		cin>>choice;
	}
	out1.close();
	out2.close();
	f1.close();
	f2.close();
	return 0;
}
