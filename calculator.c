#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define pi 3.148
void itoa(int, char *, int);
void reverse ( char *);
void dtoa ( double, char *);
char * ftoa ( double c );
char * remspace ( void );
char * strch ( char *s, int ch1, int ch2);
char * cal (  char s[] );
char * insert ( char *s , char * p );
double caltrig ( char s[] );
int strptr ( char * s, char * p);
char * insertrig( char *,char *, int);
int charcount(char * , char);


char * cal (  char s[] )
{   //printf("cin\n");
	double opr[1]; int i = 0,j = 0; double res; int len = strlen (s); char k[20]; int dup =0 ;double frac[1];
	//printf("%s\n",s);
	char *p;
	p = (char *) malloc(len + 1);
	while(s[i]!='\0') 
	{
		if(s[i] != '(' && s[i] != ')' && s[i] !=' ') k[j++] = s[i];i++;
	} k[j] = '\0'; i = 0; 
	strcpy(s,k); 	j = 0;
	while ( s[i] != '\0')
	{
		if(islower(s[i])) { j = 1; break;}i++;
	} //printf("j -- %d\n",j);
	if( j ) 
	{   
		res = caltrig(s);
		p = ftoa (res);
		strcpy(s,p);//printf("cout\n");
		return s;		
	}i = 0;
	while(s[i] != '\0')
	{
		switch (s[i])
		{
			case '+': case '*' : case '/': case '%': dup = i;  break; 
		
		} 
		if(dup > 0) break;
		if(s[i] == '-') dup = i;//printf("dup -- %d\n", dup);
		i++;
	}//printf("%c",*(s+dup));
	opr[0] = atof ( s ); char * first_operator = ftoa ( opr[0] ); i = strlen (first_operator );
	opr[1] = atof ( s + dup + 1 );//printf("s -- %s  %c\n",s, *(s+dup));
	switch(*(s+dup))
	{
		case '+' : res = (double)opr[0] + opr[1]; break;
		case '-' : res = (double)opr[0] - opr[1]; break;
		case '*' : res = (double)(double)opr[0] * opr[1]; break;
		case '/' : if(opr[1] == 0.0) { printf("Error"); break ;}
		           else res =(double) opr[0] / opr[1]; break;
		case '%' : if(!modf(opr[0] , &frac[0]) && !modf(opr[1],&frac[1]) && (opr[1] != 0.0))
		            res = (int)opr[0] % (int)opr[1]; break;
	} //printf("op1 -- %g\t  %c  op2 -- %g\n",opr[0],*(s+dup), opr[1]);
	p = ftoa( res );
    strcpy(s,p);
    //printf("cout\n");
   return s; 
	
}

double caltrig ( char s[] )
{   //printf("trin\n");
	int si = 0; si = strptr(s,"sin");
	int ta = 0; ta = strptr(s, "tan");
	int co = 0; co = strptr(s, "cos");
	// printf("s--%s %c\n",s,*(s+si));
	double res = 0.0;
	if(si) res = (double) sin(atof(s + si));
	if(ta) res = (double) tan(atof(s + ta));
	if(co) res = (double) cos(atof(s + co));
	//printf("res--%g\n",res);
	//printf("triout\n");
	return res;	
}

int strptr ( char * s, char * p)
{
	int i = 0;
	if(strstr(s,p)) 
	{
		while(s[i] != '\0')
		{
			if(*(s + i) == *p) return i + strlen ( p );
			i ++ ;
		}
	}i = 0;
	return i;
}


char * ftoa ( double c )//converts a floating point number to a string
{
	int i = 0 , sign; char * in ; char *fra;
	if(( c ) < 0) { c = -c; sign = 0;	} else sign = 1;
	double inte; char *k;
	double fr = modf(c, &inte); 
	in = (char *) malloc ( 21 );
	fra = (char *) malloc ( 6 );
	if(fr * 10 != fr){dtoa ( fr , fra);
	itoa ( inte , in ,sign);
	char c1[] = ".";
	in = strcat(in,c1);	
	 k = strcat(in,fra);
	}
	else  {itoa ( inte , in, sign ); k = in;
	}
	return k;
	
}
void dtoa( double n, char s[])//converts the decimal part of float to string
{
	int i = 0; long int pre;double p;
	char temp2[10]; strcpy (temp2 , s);
	while(i<5) 
	    { 
	      n = n * 10; 
		  i++; 
		}
		modf(n,&p);
		int k = (int)n % 10;
		if (k >= 5)
		  {
		  	p = p + 10 - k;//printf("%g\n",p);
		  	n = p;
		  } 
		else
		  {
		  	p = p - k;
		  	n = p;
		  }
		  pre = (long int)n;
		//printf("%ld\n",pre);
		while(pre % 10 == 0)
		{  
		   pre /= 10;i--;
		}
	itoa(pre,temp2,1);
	int j = 0;char temp[i];
	if(pre%10 == pre) 
	   { while(j<i-1) temp[j++] = '0';temp[j] = '\0';
	    strcat(temp,temp2);	
	    strcpy(s,temp);}
	else strcpy (s , temp2);    
}
void itoa (int n, char s[], int sign) // converts integer to string
{   int i = 0; 
	do{
		s[i++] = n % 10 + '0';
	} while((n /= 10) > 0);if(!sign) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
 
}

void reverse (char s[] ) // reverses the string
{
	int c, i, j;
	for(i = 0 , j = strlen(s) - 1 ;i < j; i++, j--)
	{
		c    = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
char * strch ( char *s, int ch1, int ch2) // to take the string and finds the innermost parentheses
{   //printf("sin\n"); printf("sin -- %s %c\n", s , *(s + 2));
	char *p;int i = 0, j = 0, ptr1 = 0, ptr2 = 0;
	//p = NULL;
	  p = (char *) malloc ( 21 );
	  int si = 0; si = strptr(s,"sin");
	  int ta = 0; ta = strptr(s, "tan");
	  int co = 0; co = strptr(s, "cos"); 
	  double ko = 0.0; char *num;int k = 0;
	  num = (char *) malloc(15);
	  int tri = 0;
	  if(si) tri = si;
	  if(co) tri = co;
	  if(ta) tri = ta;
	  //printf("tri -- %d\n", tri);
	   ptr1 = 0; ptr2 = 0;
	  while ( *s != '\0')
	  {  s++; i++;
	  	 if(*s == ch1 ) ptr1 = i;
	  	 if(*s == ch2 ) { ptr2 = i; break; }
	  }s = s - i;   i = 0;// printf("ptr -- %d %d\n",ptr1,ptr2);
	  if(ptr1 >= 0 && ptr2 > 0 && ( tri <= ptr1 || tri > ptr2 ))
	    {
	    	for(i=0; ptr1 != ptr2 - 1 ;i++) {*(p+i) = *(s+(ptr1++)+1);} *(p+i) = '\0';
	    	return (char * ) p;
		}
	  if ( ptr1 == 0 && ptr2 == 0 && tri == 0) {strcpy (p,s); return (char*) p;  }
	  if(tri) 
	  { ptr1 = tri - 3;
	  	ko = atof(s + tri);
	  	num = ftoa(ko);
	  	k = strlen(num);ptr2 = tri + k + 1;		  	  	
	  } //printf("%d %d\n",ptr1,ptr2);
	  if(tri)
	  {
	  	if(ptr1 >= 0 && ptr2 > 0)
	    {
	    	for(i=0; ptr1 != ptr2 - 1 ;i++) {*(p+i) = *(s+(ptr1++));} *(p+i) = '\0';
	    //printf("tr -- %s\n",p);
	    	return (char * ) p;
		}
	  }
	  
	  //printf("%s\n",s);
	  //printf("sout\n");
	  return (char *) p;
}
char * insert ( char *s ,  char * p )//insert the evaluated expression into parent string again
{  	//printf("iin\n");
    int ptr1 = 0 , ptr2 = 0 ,i = 0 , count = 0;
    int cochar = charcount(s,'(');
	int si = 0; si = strptr(s,"sin");
	  int ta = 0; ta = strptr(s, "tan");
	  int co = 0; co = strptr(s, "cos"); 
	  double ko = 0.0; char *num;int k = 0;
	  num = (char *) malloc(15);
	  int tri = 0;
	  if(si) tri = si;
	  if(co) tri = co;
	  if(ta) tri = ta;
	  
	  //printf("tri -- %d\n", tri);
	  
	//printf("tr--ptr1-%d -- ptr2-%d\n",ptr1,ptr2);
	    ptr1 = 0; ptr2 = 0;
	  	while(*s != '\0')
	    {
		 s++; i++;
	  	 if(*s == '(' ) ptr1 = i;
	  	 if(*s == ')' ) { ptr2 = i; break; }
	    } s = s - i;
	
	 // printf("pa--ptr1-%d -- ptr2-%d\n",ptr1,ptr2);
	  char temp2[10]; char temp1[100];
    strcpy(temp2, p); strcpy(temp1, s);
		if( ptr1 == 0 && ptr2 == 0 && (!tri || !cochar)) strcpy(s,p);
	else if( ptr1 > 0 && ptr2 > 0&& (tri <= ptr1 || tri > ptr2))
	{
		
	int j = strlen (temp2);
	for(i = ptr1 ;i <=  ptr2 ; i++)
	{
		temp1[i] = ' ';
	} 
	for( i = ptr1 ; i < j + ptr1 ; i++)
	{
		temp1[i] = temp2[count++];
	}
	i = 0; j = strlen (s); count = 0;
	char temp3[j+1]; 
	while(temp1[i] != '\0')
	{ 
	   if( i <= ptr1 )  temp3[count++] = temp1[i]; 
	   if ( i > ptr1 && i < ptr2 && temp1[i] != ' ') temp3[count++] = temp1[i];
	   if( i >= ptr2 )  temp3[count++] = temp1[i];  
	   i++;
	}temp3[count] = '\0';
	 strcpy(s, temp3);return (char *) s;
	}
	if(tri) 
	  { ptr1 = tri - 3;
	  	ko = atof(s + tri);
	  	num = ftoa(ko);
	  	k = strlen(num);ptr2 = tri + k ;		  	  	
	  } 
	if(tri)
	  {
	  	s = insertrig(s,p,tri);
	  	return (char *)s;
	  } 
	 //printf("iout\n");
	return (char *) s;
}
char * insertrig ( char * s, char * p, int trig) // replaces the trignometric names with their values
{
	int len = 0,i = 0;
	len = strlen(s);
	char  temp1[100];
	//temp1 = (char * ) malloc( len + 5 );
	while( *s != '\0' )
	 {
	 	temp1[i++] = *s++;
	 	if(i == trig - 3) break;	 	
	 } s = s + 3;
	 double res = 0.0;
	 res = atof ( s );
	 char * k = ftoa ( res );
	 int klen = strlen(k);
	while ( *p != '\0')
	 {
	 	temp1[i++] = *p++;
	 }s = s + klen;
	while ( *s != '\0')
	 {
	 	temp1[i++] = *s++;
	 } temp1[i] = '\0';
	 //printf("temp1 -- %s\n",temp1);
	 len = strlen(temp1);
	 s = (char *) malloc(len + 1);
	strcpy(s, temp1);
	return s; 
	
}
int charcount ( char *s, char ch)//counts the number of a particular character
{
	int count = 0;
	while(*s != '\0')
	  {
	  	  if(*s == ch ) count++;
	  	  s++;
	  }
	return count;  
}
int oper ( char s[]) // counts the no. of operators
{   int len = strlen(s); int i = 0, count = 0, dup = 0;
	while(s[i] != '\0')
	{
		switch(s[i])
		{
			case '+' :  case '*': case '/': case '%': count++; break;
			case '-' : count++;if(s[i+1] !=' ') count--; break; 
		}i++;
	}i = 0;//printf("l -- %d\n",count);
	while(s[i] != '\0')
	{
		if(islower(s[i])) {dup++; count++;} ;
		i++;
	} //printf("dup -- %d\n",dup);
	if(dup){dup = dup/3; dup *=2; count -= dup;}
	//printf("l -- %d\n",count);
	return count;
}


int main()
{   
   	char s [ 100 ];
   	gets(s);
   	 int l = oper(s);
   	 int i = 0;//printf("l -- %d\n",l);
    while( l >= 0 ) 
   	{
       
    char * inn = strch ( s, '(',')');
	cal ( inn ) ;
	if(l == 1){strcpy(s,inn); break;	}
	char * k = insert ( s , inn );
	strcpy (s,k);
	l--;//printf("\n%s\n", s);
	}
	printf("%s", s);
   	return 0;
}