#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct tree
{
	int index;
	char cgpa[5];
	int lchild;
	int rchild;
};

struct student
{
	char rollno[7];
	char name[20];
	char cgpa[5];
};

ifstream & operator >> (ifstream & in,tree &s)
{
	char ch;int i=0;
	int ctr=1;
	s.index=0;
	while(ctr!=5)
	{
		in>>ch;
		if(ch=='$')
		{
		ctr++;
		continue;
	    }
		if(ctr==1)
		{
			s.index=s.index*10+(ch-'0');
	    }
		if(ctr==4)
		{
			s.cgpa[i]=ch;
			i++;
		}
	}
	s.cgpa[i]='\0';
	s.lchild=-1;
	s.rchild=-1;
	return in;
}

int k;

void insert(tree T[],tree M,int l)
{
	int x=strcmp(T[k].cgpa,M.cgpa);
	{
		if(x==1)
		{
			if(T[k].lchild!=-1)
			{k=T[k].lchild;
			insert(T,M,k);
		    }
			else
			{
			    T[k].lchild=M.index;
		    }
		}
		else
		{
			if(T[k].rchild!=-1)
			{k=T[k].rchild;
			insert(T,M,k);
		    }
			else
			{
			    T[k].rchild=M.index;
			    M.rchild=-1;
			    M.lchild=-1;
			}
		}
	}
}

int l;
void store(tree T[],ofstream &out,int k)
{
	    for(int i=0;i<k-1;i++)
	    out<<T[i].lchild<<" "<<T[i].index<<" "<<T[i].cgpa<<" "<<T[i].rchild<<endl;
}

int search(tree T[],char c[],int k)
{
	int x=strcmp(T[k].cgpa,c);
	if(x==1)
	{
		k=T[k].lchild;
		if(k!=-1)
		return search(T,c,k);
	}
	else if(x==-1)
	{
		k=T[k].rchild;
		if(k!=-1)
		return search(T,c,k);
	}
	else if(k==-1)
	return NULL;
	else
	return T[k].index;
}

ifstream & operator >> (ifstream & in,student &s)
{
	char ch;int i=0;in>>ch;
	while(ch!='$')
	{
		in>>ch;
	}
	in>>ch;
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
	ifstream in("datafile1.txt");
	tree I[100];
	student s;
    int a,i=0;
    while(!in.eof())
    {
    	in>>I[i];
    	i++;
    }
    I[0].lchild=-1;I[0].rchild=-1;
    I[0].index=0;
    for(int j=1;j<i-1;j++)
    {
    	k=0;
    	I[j].index=j;
        insert(I,I[j],k);
    }
    in.close();
    ofstream out("sort.txt");
    k=i;
    store(I,out,k);
    char cg[5];
    cout<<"Enter cgpa to search: ";
    cin>>cg;
    k=0;
    i=search(I,cg,k);
    int j=0;
    if(i!=-1)
    cout<<"Cgpa given is found at index: "<<i;
    
    else
    cout<<"Cg not found!!!";
	return 0;
}
