#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class student
{
	public:
		char rollno[6];
		char name[10];
		char cgpa[4];
};
struct buffer
{
	char buff[25];
    void pack(char a[]);
    void store(ofstream &out);
};
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
	buffer b;
	cout<<"Enter roll no:";
	cin>>s.rollno;b.pack(s.rollno);
	cout<<"Enter name:";	
	cin>>s.name;b.pack(s.name);
	cout<<"Enter cgpa:";
	cin>>s.cgpa;	b.pack(s.cgpa);
    out.open("buffer.txt");
	b.store(out);
	out.close();	
	return 0;
}
