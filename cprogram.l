%{
   #include<stdio.h>
%}

%%

[a-zA-Z]   printf("1");
"abc"      printf("2");
(ab)+      printf("3");

%%
