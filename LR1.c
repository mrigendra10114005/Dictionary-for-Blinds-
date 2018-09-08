 #include<stdlib.h>
#include<ctype.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
char table[15][15][10]={{"s5"," "," ","s4"," "," ","1","2","3"},
{" ","s6"," "," "," ","acc"," "," "," "},{" ","r2","s7"," ","r2","r2"," "," "," "},
{" ","r4","r4"," ","r4","r4"," "," "," "},{"s5"," "," ","s4"," "," ","8","2","3"},
{" ","r6","r6"," ","r6","r6"," "," "," "},{"s5"," "," ","s4"," "," "," ","9","3"},
{"s5"," "," ","s4"," "," "," "," ","10"},{" ","s6"," "," ","s11","s1"," "," "," "},
{" ","r1","s7"," "," ","r1","r1"," "," "},{" ","r3","r3"," ","r3","r3","r3"," "," "},
{" ","r5","r5"," "," ","r5","r5"," "," "}};
char prod[15][15]={" "," ","E","E+T","E","T","T","T*F","T","F","F","(E)","F","i" };
char action[10][10]={"i","+","*","(",")","$","E","T","F"};
int top=0,t=0,prodnum=7;
char stack[25],ip[25];
void get()
{
cout<<"enter the input (i for id): \n";
cin>>ip;
cout<<"STACK \t INPUT STRING \t REMARKS \n";
strcat(ip,"$");
strcpy(stack,"0");
}
int retpos(char p)
{
int i=0;
char temp[10];
temp[0]=p;
temp[1]='\0';
while(action[i]!='\0')
{
if(strcmp(temp,action[i])==0)
return i;
i++;
}
return -1;
}
char *poptop()
{
char *x;
int i=0,j=top;
while(isdigit(stack[j])>0&&j>=0)
{
x[i]=stack[j];
i++;
j--;
}
x[i]='\0';
strrev(x);
return x;
}
void slr()
{
char test[20],temp[10],pop[10];
int x,y,c,red=0,flag=1,p=0,t=0,h=0;
int look=0;
while(ip[p]!='\0')
{
strcpy(test,poptop());
x=atoi(test);
y=retpos(ip[p]);
if(y!=-1)
{
strcpy(temp,table[x][y]);
}
if(temp[0]=='s')
{
red=0;
stack[++top]=ip[p];
c=1;
while(temp[c]!='\0')
stack[++top]=temp[c++];
stack[top+1]='\0';
p++;
}
else if(temp[0]=='r')
{
red=1;
c=0;
while(temp[c]!='\0')
{
temp[c]=temp[c+1];
c++;
}
h=atoi(temp);
h*=2;
strcpy(pop,prod[h+1]);
t=strlen(pop);
t*=2;
if(top>=t)
{
top=top-t;
while(isalpha(stack[top])>0)
top--;
stack[top+1]='\0';
}
strcpy(temp,poptop());
strcat(stack,prod[h]);
top+=strlen(prod[h]);
strcpy(test,table[atoi(temp)][retpos(stack[top])]);
strcat(stack,test);
top+=strlen(test);
stack[top+1]='\0';
}
else if(strcmp(temp,"acc")==0)
{cout<<"accepted";
return;
}
else
{
cout<<"error";
flag=0;
return;
}
cout<<stack<<"\t\t";
for(int d=p;ip[d]!='\0';d++)
cout<<ip[d];
if(red==0)
cout<<" shift ";
if(look==1&&red==1)
{cout<<"reduce"<<" "<<prod[h]<<" -->"<<prod[h+1];}
look=1;
cout<<"\n";
}
getch();
}
void main()
{
clrscr();
get();
slr();
getch();
}














