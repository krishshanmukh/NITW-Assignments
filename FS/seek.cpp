#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ofstream oh("seek.txt");
	oh.close();
	fstream f("seek.txt",ios::out|ios::in);
	f<<"@#!#@\n69";cout<<f.tellp();
	int r=4;
	f.seekp(7,ios::beg);
	f<<"!@#$";
	cout<<f.tellp();
	f<<"HI";
	cout<<f.tellp();
	f.close();
	return 0;
}
