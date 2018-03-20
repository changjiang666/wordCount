#include "CLinkList.h"
#include <stdio.h>


//tail insert every node, if input 0 end the process
void InitCLinkList(CLinkList *L)
{
	CLinkList *curr = L, tmp;
	int data;
	printf("please input the data\n");
	scanf_s("%d", &data);
	fflush(stdin);
	if (*L != NULL)
		curr = &((*curr)->next);
	for (; *curr != *L; curr = &((*curr)->next))
		;
	while (data)
	{
		tmp = (CLinkList)malloc(sizeof(Node));
		if (!tmp)
			exit(0);
		tmp->data = data;
		*curr = tmp;
		tmp->next = *L;
		curr = &(tmp->next);
		scanf_s("%d", &data);
		fflush(stdin);
	}
	
}

int LengthCLinkList(CLinkList *L)
{
	int length = 1;
	CLinkList *curr;
	for (curr = L; (*curr)->next != *L; curr = &((*curr)->next),++length);
	return length;
}

Status InsertCLinkList(CLinkList *L, int i)
{
	CLinkList *curr = L;
	CLinkList tmp;
	int j = 0;
	ElemType e;
	printf("please input the insert node of data:");
	scanf_s("%d", &e);
	if (i < 1 || i > LengthCLinkList(L) + 1)
		return ERROR;

	if (i == 1)
		for (curr = &((*curr)->next); *curr != *L; curr = &((*curr)->next))
			;
	else
		for (; j < i - 1; curr = &((*curr)->next), ++j);	
	tmp = (CLinkList)malloc(sizeof(Node));
	if (!tmp)
		exit(0);
	tmp->data = e;
	tmp->next = *curr;
	*curr = tmp;
	if (i == 1)
		*L = tmp;
	return OK;	
}

Status DeleteCLinkList(CLinkList *L, int i)
{
	int j = 0;
	CLinkList *curr;
	CLinkList tmp;
	if (!*L)
		return ERROR;
	if (i < 1 || i > LengthCLinkList(L))
		return ERROR;

	if (i == 1)
	{
		for (curr = L; (*curr)->next != *L; curr = &((*curr)->next));
		curr = &((*curr)->next);
		tmp = *curr;
		*curr = tmp->next;
		*L = *curr;
	}
	//else
	{
		for (curr = L; j < i - 1; curr = &((*curr)->next), ++j);
		tmp = *curr;
		*curr = tmp->next;
	}
	free(tmp);
}

int SearchCLinkList(CLinkList *L, ElemType e)
{
	int j = 1;
	CLinkList *curr;
	if (!*L)
		return ERROR;
	for (curr = L; (*curr)->data != e && (*curr)->next != *L; curr = &((*curr)->next), ++j);
	if ((*curr)->next == *L && (*curr)->data != e)
		return ERROR;
	return j;
}

void TraverseCLinkList(CLinkList *L)
{
	CLinkList *curr = L;
	if (!*L)
		return ERROR;

	printf("%4d ", (*curr)->data);
	for (curr = &((*L)->next); (*curr) != *L; curr = &((*curr)->next))
		printf("%4d ", (*curr)->data);
}