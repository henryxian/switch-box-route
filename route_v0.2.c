#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"

typedef struct linknode
{
	int number;
	struct linknode *next;
}LiStack;//definition of the stack struct

void initStack(LiStack *&s)//initialize the stack
{
	s = (LiStack *) malloc (sizeof(LiStack));
	s->next = NULL;
}

void clearStack(LiStack *&s)//clear the stack and free the space
{
	LiStack *p, *q;
	p = s;
	q = s->next;
	while(q!=NULL)
	{
		free(p);
		p = q;
		q = p->next;
	}
	free(p);
}

int isEmpty(LiStack *s)//check if the stack is empty or not
{
	return(s->next == NULL);
}

void push(LiStack *&s, int d)//push a node
{
	LiStack *p;
	p = (LiStack *) malloc(sizeof(LiStack));
	p->number = d;
	p->next = s->next;
	s->next = p;
}

int pop(LiStack *&s)//pop a node
{
	LiStack *p;
	if(s->next == NULL)
		return 0;
	p = s->next;
	s->next = p->next;
	free(p);
	return 1;
}

int top(LiStack *s)//get the top element of the stack
{
	if(s->next == NULL)
		return 0;
	return s->next->number;
}

void  checkBox(int net[], int n)//check if the box is routable or not
{
	int i;
	LiStack *s;
	initStack(s);
	for (i = 0; i < n; ++i)
	{
		if(!isEmpty(s))
		{
			if(net[i] == top(s))
				pop(s);
			else
				push(s, net[i]);
		}
		else
		{
			push(s, net[i]);
		}
	}
	if(isEmpty(s))
		printf("The box is routable.\n");
	else
		printf("The box is not routable\n");
	free(s);
}

int checkFloat(char s[])
{
	for(int i = 0;i < strlen(s);i++)
	{
		if(s[i] == '.')
		{
			return 1;
		}
	}
	return 0;
}

int  main()
{
	while(1)
	{
		char b[20];
		int n;
		printf("please input the number of the ports, the number should not be EVEN.\n");
		scanf("%s", b);
		n = atoi(b);//array to integer method call
		while(n % 2 != 0 || n < 0 || n == 0 || checkFloat(b))
		{
			printf("wrong input.please input again: \n");
			scanf("%s", b);
			n = atoi(b);
		}
		printf("please input the responsable net of the port\n");
		int a[100];
		int net[50];
		for(int j = 0; j < (n/2); j++)
		{
			a[j] = 2;
		}
		for(int i = 0; i < n; i++)
		{
			char s[100];
			printf("port %d:", (i + 1));
			scanf("%s", s);
			if(!atoi(s) || checkFloat(s))
			{
				printf("wrong input!\n");
				i--;
				continue;
			}
			else if((atoi(s) > 0) && ((atoi(s) < (n/2)) || (atoi(s) == (n/2))))
				{
					int b;
					b = atoi(s);
					if(a[(b-1)] > 0)
					{
						//printf("a[%d]:%d\n", b-1, a[b-1]);
						a[(b-1)]--;
						net[i] = b;
					}
					else
					{
						printf("this net already has two ports, please input again!\n");
						i--;
						continue;
					}
				}
			else 
			{
				printf("wrong input!\n");
				i--;
				continue;
			}
		}
		checkBox(net, n);
		printf("----------------------------------------------------------------------------\n");
	}
	/*int net[] = {1, 2, 3, 4, 1, 4, 3, 2};
	checkBox(net, 8);
	int net2[] = {1, 2, 2, 1, 3, 4, 4, 3};
	checkBox(net2, 8);
	int net3[] = {1, 2, 2, 1, 3, 4, 5, 5, 4, 3, 6, 6, 7, 7};
	checkBox(net3, 14);
	return 0;*/
}
