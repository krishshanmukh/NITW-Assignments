#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
using namespace std;
class student
{
	public:
		char rno[6];
		char name[20];
		char cgpa[4];
};
ifstream & operator >> (ifstream & in,student &s)
{
	in>>s.rno;
	in>>s.name;
	in>>s.cgpa;
	return in;
}
ofstream & operator << (ofstream &out, student &s)
{
	out<<s.rno;
	out<<s.name;
	out<<s.cgpa;
	return out;
}
int main()
{
	ifstream in;
	ofstream out("studcpy.txt");
	in.open("stud.txt");
	if(in.fail()||out.fail())
	exit (0);
	student s1;
	in>>s1;
	out<<s1;
	out.close();
	in.close();
	return 0;
}
