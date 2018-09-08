#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iostream.h>
#include<dos.h>


char a[8][5],b[7][5];
int c[12][5];
int w=0,e=0,x=0,y=0;
int st2[12][2],st3[12];
char sta[12];


void st1(char,int);
void st(char,int,int,int);


void main()
 {
  int i,j,k,l=0,m=0,p=1,f=0,g,v=0,jj[12];
  clrscr();
  printf("

	*******Enter the Grammar Rules (max=3)*******
	");
  for(i=0;i<3;i++)
   {
	gets(a[i]);
	printf("	");
	}
  for(i=0;i<3;i++)
   {
	for(j=0;j<strlen(a[i]);j++)
	 {
	  for(k=0;k<strlen(a[i]);k++)
	   {
		if(p==k)
		{
		 b[l][m]='.';
		 m+=1;
		 b[l][m]=a[i][k];
		 m+=1;
		 }
		else
		{
		   b[l][m]=a[i][k];
		   m++;
		 }
		}
		p++;
		l++;
		m=0;
	  }
	  p=1;
	}
 i=0;
 p=0;
 while(l!=i)
 {
 for(j=0;j<strlen(b[i]);j++)
  {
   if(b[i][j]=='.')
	{
	 p++;
	 }
   }
  if(p==0)
   {
	b[i][strlen(b[i])]='.';
	}
   i++;
   p=0;
  }
  i=0;
 printf("
	*******Your States will be*******
	");
 while(l!=i)
  {
   printf("%d--> ",i);
   puts(b[i]);
   i++;
   printf("	");
   }
   printf("
");
 v1('A',l);
 p=c[0][0];
 m=0;
 while(m!=6)
 {
 for(i=0;i<st3[m];i++)
  {
   for(j=0;j<strlen(b[p]);j++)
   {
   if(b[p][j]=='.' && ((b[p][j+1]>=65 && b[p][j+1]<=90)||(b[p][j+1]>=97&&b[p][j+1]<=122)))
	 {
	  st2[x][0]=m;
	  sta[x]=b[p][j+1];
	  v2(b[p][j+1],j,l,f);
	  x++;
	  //str();
	  }
	else
	 {
	   if(b[p][j]=='.')
	   {
		st2[x][0]=m;
		sta[x]='S';
		st2[x][1]=m;
		x++;
		}

	   }
	}
	 p=c[m][i+1];
   }
   m++;
   p=c[m][0];
 }
 g=0;
 p=0;
 m=0;
x=0;
while(p!=11)
 {
 for(i=0;i<st3[p];i++)
  {
	for(k=0;k<p;k++)
	{
	 for(j=0;j<3;j++)
	 {
	   if(c[k][j]==c[p][j])
		{
		 m++;
		 }
	 }
	if(m==3)
	 {
	  m=0;
	  goto ac;
	  }
	 m=0;
   }
	 if(m!=3)
	 {
	  if(v==0)
	   {
		 printf("	I%d=",g);
		 v++;
		 jj[g]=p;
		}
	  printf("%d",c[p][i]);
	  }

 }

  printf("
");
  g++;
  ac:
  p++;
  v=0;
  }
 printf("	*******Your DFA will be *******");
 for(i=0;i<9;i++)
  {
   printf("
	%d",st2[i][0]);
   printf("-->%c",sta[i]);
   }
 getch();
 }
void v1(char ai,int kk)
 {
  int i,j;
  for(i=0;i<kk;i++)
   {
	if(b[i][2]==ai&&b[i][1]=='.')
	 {
	   c[w][e]=i;
	   e++;
	   if(b[i][2]>=65 && b[i][2]<=90)
		{
		 for(j=0;j<kk;j++)
		  {
		   if(b[j][0]==ai && b[j][1]=='.')
			{
			 c[w][e]=j;
			 e++;
			 }
			}
		   }
	   }
	}
	st3[w]=e;
	w++;
	e=0;
  }
void v2(char ai,int ii,int kk,int tt)
 {
   int i,j,k;
   for(i=0;i<kk;i++)
	{
	 if(b[i][ii]=='.'&& b[i][ii+1]==ai)
	  {
	   for(j=0;j<kk;j++)
		{
		 if(b[j][ii+1]=='.' && b[j][ii]==ai)
		  {
			c[w][e]=j;
			e++;
			st2[tt][1]=j;
			if(b[j][ii+2]>=65 && b[j][ii+1]<=90)
			 {
			  for(k=0;k<kk;k++)
			   {
			   if(b[k][0]==b[j][ii+2] && b[k][1]=='.')
				{
				 c[w][e]=k;
				 e++;
				 }
			   }
			 }
			}
		  }
		  if((b[i][ii+1]>=65 && b[i][ii+1]<=90) && tt==1)
		   {
			for(k=0;k<kk;k++)
			 {
			  if(b[k][0]==ai && b[k][1]=='.')
			   {
				 c[w][e]=k;
				 e++;
				 }
			}
		 }
		}
	  }
	  st3[w]=e;
	  w++;
	  e=0;
	  }





			