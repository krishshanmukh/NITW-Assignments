#include<iostream>
#include<cstring>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

int dir[32],C[10],d=0,ctr=1;

struct buffer
{
	char buff[100];
	int d;
    void pack(char a[]);
}b[10];

void buffer :: pack (char a[])
{
	strcat(buff,a);
}

int fold_key(int key)
{
	return key%256;
}

void convert_into_binary(char ch[],int r)
{
	int x=128,i=0,temp;
	while(x!=0)
	{
		temp=r/x;
		if(temp==0)
		ch[i++]='0';
		else
		ch[i++]='1';
		r=r%x;
		x/=2;
	}
	ch[8]='\0';
	cout<<r<<" "<<ch<<endl;
}

int get_decimal(char ch[],int d)
{
	int x=pow(2,d-1),value=0,i=0;
	while(i<d)
	{
		if(ch[i++]=='1')
		value+=x;
		x/=2;
	}
	return value;
}
 
int get_file_position(int r,int d)
{
	char ch[9];
	convert_into_binary(ch,r);
	return get_decimal(ch,d);
}

void get_record(char bu[],char ch[],int i)
{
	int m=strlen(bu),count=1,j=0;cout<<i;
	for(int k=0;k<m;k++)
	{
		if(count==i)
		{
			while(bu[k]!='|')
			{
				ch[j++]=bu[k++];
			}
			ch[j]='\0';
			break;
		}
		if(bu[k]=='|')
		count++;
	}
}
void create(int key,char record[]);
int split_bucket(int r)
{
	int count=0,i;
	for(i=0;i<pow(2,d);i++)
	{
		if(dir[i]==dir[r])
		{
			while(dir[i]==dir[r])
			{
				count++;i++;
			}
			break;
		}
	}
	if(count==1)
	return 0;
	else
	{
		for(int j=i-count/2;j<i;j++)
		{
			dir[j]=ctr;
		}
		b[ctr].d=++b[dir[i-count]].d;
		ctr++;
		char bu[20];
		strcpy(bu,b[dir[r]].buff);cout<<i<<count;
		b[dir[r]].buff[0]='\0';
		C[dir[i-count]]=0;
		C[dir[r]]=0;
		for(int j=1;j<6;j++)
		{
			char ch[20];cout<<j;
			get_record(bu,ch,j);
			cout<<ch<<endl;
			create(atoi(ch),ch);
		}
		return 1;
	}	
}

void dir_extend()
{
	int ndir[32];
	int p=pow(2,d);d++;
	for(int i=0;i<p;i++)
	{
		ndir[2*i]=dir[i];
		ndir[2*i+1]=dir[i];
	}
	p=pow(2,d);
	for(int i=0;i<p;i++)
	dir[i]=ndir[i];
}

void create(int key,char record[])
{
	int k=fold_key(key);
	int r=get_file_position(k,d);
	cout<<"Key: "<<k<<" File pos: "<<d<<" "<<r<<endl;
	if(C[dir[r]]!=5)
	{
		b[dir[r]].pack(record);
		++C[dir[r]];
	}
	else
	{
		int choice=split_bucket(r);
		if(choice==0)
		dir_extend();
		create(key,record);
	}
}

int main()
{
	int key,choice=1;
	char ch[20],data[10];
	for(int i=0;i<10;i++)
	{
		C[i]=0;
		dir[i]=1000;
	}
	dir[0]=0;
	b[0].d=0;
	while(choice==1)
	{
		cout<<"Enter key: ";
		cin>>key;
		itoa(key,data,10);
		strcpy(ch,data);
		strcat(ch," ");
		cout<<"Enter name: ";
		cin>>data;
		strcat(ch,data);
		strcat(ch," ");
		cout<<"Enter cgpa: ";
		cin>>data;
		strcat(ch,data);
		strcat(ch,"|");
		create(key,ch);
		cout<<"Enter choice: ";
		cin>>choice;
	}
	for(int i=0;i<4;i++)
	cout<<b[i].buff<<" ";
}
