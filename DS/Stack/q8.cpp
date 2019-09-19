#include<iostream>
#include<cstring>
using namespace std;
union datatype
{
    int i;
    char ch;
};
class stack
{
public:
    datatype e[150];
    int size=150;
    int top=-1;
    int chc=-1;
    int topc=-1;
    void pushi(int a);
    void pushc(char a);
    int popi();
    char popc();
};
void stack::pushi(int a)
{
    if(top<size-1)
        e[++top].i=a;
    else
        cout<<"\nStack is Full!\n";
}
void stack::pushc (char a)
{
    if(top<size-1)
        {
            chc++;
            e[++top].ch=a;
            topc=top;
        }
    else
        cout<<"\nstack is full!\n";
}
int stack::popi()
{
    if(top>=0)
        return e[top--].i;
    else
        cout<<"\nStack is Empty\n";
}
char stack::popc()
{
    if(top>=0)
        {
            chc--;
            return e[top--].ch;
            topc=top;
        }
    else
        cout<<"\nstack3 is epmty\n";
}
int main()
{
    stack sym;
    int z=0;
    char ch[150];
    cout<<"\nEnter the Infix Expression\n";
    cin.getline(ch,150);
    int l=strlen(ch);
    for(int i=0;i<l;i++)
    {
        if(ch[i]>=48&&ch[i]<=57)
        {
            int b;
            b=int(ch[i])-48;
            sym.pushi(b);
        }
         else if((ch[i]=='+'||ch[i]=='*'||ch[i]=='-'||ch[i]=='/')&&sym.chc==-1)
                sym.pushc(ch[i]);
         else if((ch[i]=='*'||ch[i]=='/')&&(sym.e[sym.topc].ch=='-'||sym.e[sym.topc].ch=='+'))
                sym.pushc(ch[i]);
         else
         {
             while(sym.chc>-1)
             {
                 int x,y;
                 char c;
                 y=sym.popi();
                 c=sym.popc();
                 x=sym.popi();
                 if(c=='+')
                 z=x+y;
                 else if(c=='-')
                 z=x-y;
                 else if(c=='*')
                 z=x*y;
                 else if(c=='/')
                 z=x/y;
                 sym.pushi(z);
             }
             sym.pushc(ch[i]);
         }
    }
          while(sym.chc>-1)
             {
                 int x,y;
                 char c;
                 y=sym.popi();
                 c=sym.popc();
                 x=sym.popi();
                 if(c=='+')
                 z=x+y;
                 else if(c=='-')
                 z=x-y;
                 else if(c=='*')
                 z=x*y;
                 else if(c=='/')
                 z=x/y;
                 sym.pushi(z);
             }
             cout<<z;
    return 0;
}
