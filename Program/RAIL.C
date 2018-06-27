#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10
int z=0;

char queue[MAX][MAX];
int l=-1,r=-1;
int key[MAX],table[MAX]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int graph[5][5]={0};
char list[MAX][MAX];
struct node
{
 char station[100];
 struct node *next;
};
struct node *start=NULL;

void insert();
void delet();
void linear(int i,int table[MAX],int key[MAX]);
void display();
void disp_list();
struct node* create();
void disp(struct node *start,int s,int d);

void main()
{
  int ch,s,d,r,j,k,n,i,M=10;
  clrscr();
  start=create();
  do
  {
    printf("\n\nMAIN MENU");
    printf("\n1.Add new passenger \n2.Call next passenger \n3.Book ticket \n4.Print list for TC \n5.Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
      case 1:
      {
	insert();
	break;
      }
      case 2:
      {
	printf("\nNext Passenger: ");
	puts(queue[l]);
	break;
      }
      case 3:
      {
	printf("\n1.Dadar 2.Thane 3.Nasik 4.Manmad 5.Aurangabad");
	printf("\n\nEnter source and destination stations: ");
	scanf("%d %d",&s,&d);
	printf("\nEnter 1 for single journey and 2 for return journey: ");
	scanf("%d",&r);
	if(r==1)
	{
	  for(j=s-1;j<d;j++)
	  {
	    for(k=j;k<d;k++)
	    {
	      graph[j][k]=1;
	    }
	  }
	}
	else if(r==2)
	{
	  for(j=s-1;j<d;j++)
	  {
	    for(k=s-1;k<d;k++)
	    {
	      graph[j][k]=1;
	    }
	  }
	}
	else
	{
	  printf("\nInvalid Entry!");
	}
	display();
	printf("\nEnter the no. of seats: ");
	scanf("%d",&n);
	if(n>M)
	{
	  printf("No. of seats exceeded");
	}
	else
	{
	  M=M-n;
	  for(i=0;i<n;i++)	//Accepting elements from user
	  {
	    key[i]=i;	//Assigning key
	    linear(i,table,key);
	  }
	  disp(start,s,d);
	}
	delet();
	break;
      }
      case 4:
      {
	disp_list(M);
	break;
      }
    }
  }while(ch!=5);
  printf("\n\nProgram by Mihir Gandhi B1 1611077");
  getch();
}

void insert()
{
  int i;
  char name[MAX];
  printf("\nEnter name: ");
  scanf(" %s",&name);
  if((l==0&&r==MAX-1)||(l==r+1))
  {
    printf("\nOverflow");
    return;
  }
  if (l==-1) 	//check for empty
  {
    l=0;
    r=0;
  }
  else
  {
    if(r==MAX-1) 	//r is at last position of queue
    {
      r=0;
    }
    else
    {
      r=r+1;
    }
  }
  for(i=0;name[i]!='\0';i++)
  {
    queue[r][i]=name[i];
  }
}

void delet()
{
  if(l==-1)
  {
    printf("\nUnderflow");
    return;
  }
  if(l==r) 		//when Queue has only one element
  {
    l=-1;
    r=-1;
  }
  else
  {
    if(l==MAX-1)
    {
      l=0;
    }
    else
    {
      l=l+1;
    }
  }
}

void linear(int i,int table[MAX],int key[MAX])
{
  int j,h,k;
  h=key[i]%MAX;		//Determining index using hash function
  if(table[h]==-1)		//If the position at given index is free i.e. no collision
  {
    table[h]=i;		//Entering the element in table
  }
  else			//If there is a collision
  {
    for(j=1;j<MAX;j++)
    {
      h=(h+j)%MAX;		//New index using linear probing technique
      if(table[h]==-1)	//Checking for collision again
      {
	break;
      }
    }
    table[h]=i;		//Entering the element in table
  }
  for(k=0;queue[l][k]!='\0';k++)
  {
    list[z][k]=queue[l][k];
  }
  z++;
  printf("\nSeat number %d booked",h+1);
}

void display()
{
  int i,j;
  printf("\nYou can travel between the pairs of stations marked as 1 (Row to column):\n");
  printf("*  1 2 3 4 5\n");
  for(i=0;i<5;i++)
  {
    printf("%d  ",i+1);
    for(j=0;j<5;j++)
    {
      printf("%d ",graph[i][j]);
    }
    printf("\n");
  }
}

struct node* create()
{
  char stn[MAX][MAX]={"Dadar","Thane","Nasik","Manmad","Aurangabad"};
  int j=0;
  struct node *ptr,*start1;
  ptr=start1;
  strcpy(ptr->station,stn[j]);
  j++;
  while(j<5)
  {
    ptr->next=(struct node*)malloc(sizeof(struct node));
    ptr=ptr->next;
    strcpy(ptr->station,stn[j]);
    j++;
  }
  ptr->next=NULL;
  return start1;
}

void disp(struct node *start,int s,int d)
{
  int i;
  struct node *ptr=start;
  printf("\n\nYour path is: ");
  for(i=1;i<s;i++)
  {
    ptr=ptr->next;
  }
  while(i!=d+1)
  {
    printf(" %s",ptr->station);
    printf("->");
    ptr=ptr->next;
    i++;
  }
  printf("END");
}

void disp_list(int M)
{
  int i,j;
  printf("\nRESERVATION LIST\n");
  for(i=0;i<MAX-M;i++)
  {
    printf("%d.",i+1);
    for(j=0;list[i][j]!='\0';j++)
    {
      printf("%c",list[i][j]);
    }
    printf("\n");
  }
}