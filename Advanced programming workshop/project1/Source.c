
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define M 3
#define N 3
#define P 2

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();

/* struct declaration */

//EX3 
typedef struct create_three_var {
	int value, i, j;
}create_three_var;

typedef struct three_list {
	struct create_three_var data;
	struct three_list *next;
}three_list;

//EX4
typedef struct list
{
	int value;
	struct list* next;
}list;

/* Declarations of other functions */

//EX1 functions
unsigned int powerArray(int n);
void array_print(unsigned int *arr, int n);

//EX2 functions
int **DynamicMatrix(int r, int c);
int **matrixMultiplication(int matrixA[M][N], int matrixB[N][P], int **matrixC);
void printMatrix(int **matrix, int r, int c);
void freeMatrix(int **matrix, int r);

//EX3 functions
int createArrayAndList(int **matrix, int r, int c, create_three_var **arr, three_list **head);
int createThreeArr(create_three_var **arr, int **matrix, int r, int c, int count);
create_three_var createThree(int i, int j, int value);
int createThreeList(three_list **head, create_three_var **arr, int count);
void printListEx3(three_list *head);
void freeListEx3(three_list *head);

//Ex4 functions
list *buildOriginalList();
list *createList(list **even_head);
list *Insert(list** head, list** tail, int val);
int Delete(list *temp);
void printList(list *head);
void freeList(list *head);

//Ex5 functions
list *createList2(list **even_head);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 5; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-5 : ");
				scanf("%d", &select);
			} while ((select < 0) || (select > 5));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}



/* Function definitions */

/* ------------------- */

/*....ex1....*/
void Ex1()
{
	int n;
	printf("please enter the length of the array:");
	scanf("%d", &n);//����� ������� �� ���� �� ������ ���� ���� �����
	unsigned int *p = powerArray(n);//����� ����� ����� �������� ����� �� ����� �����
	array_print(p, n);//����� ����� ����� ������ �������� �����

	system("pause");
	free(p);
}

unsigned int powerArray(int n)//�������� ����� ���� ���, ���� ���� ���� �����, ������ �� ����� ����� ��"� ������ �� 2 ����� ����� ������ �� ������� �32
{
	unsigned int *p = (unsigned int*)malloc(n * sizeof(unsigned int));
	int i;
	
	if (!p)
	{
		printf(" not enough memory \n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		if (i % 32 == 0)
		{
			p[i] = 1;
		}
		else
		{
			p[i] = 2 * p[i - 1];
		}
	}
	return p;
	free(p);
}

void array_print(unsigned int *arr, int n)//������� ������ ����� ����� ������ ������� �� ����� 
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("arr[%d]=%u\n", i, arr[i]);
	}
	printf("\n");
}


/*....ex2....*/

void Ex2()
{
	int matrixA[M][N], matrixB[N][P];
	int i, j;
	int **matrixC;

	printf("Type in values for matrix A with %d rows and %d colls\n", M, N);
	for (i = 0; i < M; i++)//A����� ����� �������
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &matrixA[i][j]);
		}
	}

	printf("Type in values for matrix B with %d rows and %d colls\n", N, P);
	for (i = 0; i < N; i++)//B ����� ����� �������
	{
		for (j = 0; j < P; j++)
		{
			scanf("%d", &matrixB[i][j]);
		}
	}

	matrixC = DynamicMatrix(M, P);//����� ������ �� ������� �������� ����� �� ������� ��������
	matrixC = matrixMultiplication(matrixA, matrixB, matrixC);//����� �������� �������� ����� �� ���� �����
	
	printf("matrix A is:\n");//A ����� ������
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%6d", matrixA[i][j]);
		}
		printf("\n");
	}
	printf("matrix B is:\n");//B ����� ������
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < P; j++)
		{
			printf("%6d", matrixB[i][j]);
		}
		printf("\n");
	}
	printf("matrix c is:\n");
	printMatrix(matrixC, M, P);//C ����� ������ ����
	
	system("pause");
	freeMatrix(matrixC, M);//����� ����� ������ ������� ����� ������� ������
}

int **DynamicMatrix(int r, int c)//������� ����� ������ �������
{
	int i;
	int **matrix = (int**)calloc(r , sizeof(int*));
	for (i = 0; i < r; i++)
	{
		matrix[i] = (int*)calloc(c , sizeof(int));
	}
	return matrix;
}

int **matrixMultiplication(int matrixA[M][N], int matrixB[N][P], int **matrixC)//������� ������ �� ��� �������� ������ �� ���� �����, �������� ������ �� ������ ������� ����
{
	int i, j, k;
	for (i = 0; i < M; i++)
	{
		for (k = 0; k < P; k++)
		{
			for (j = 0; j < N; j++)
			{
				matrixC[i][k] += matrixA[i][j] * matrixB[j][k];
			}
		}
	}
	return matrixC;
}

void printMatrix(int **matrix, int r, int c)//������� ������ �� ������ ������� ��� ���� ������� ������� �� �������,�������� ������ ������ �������
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			printf("%6d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void freeMatrix(int **matrix, int r)//������� ������ �� ������ ������� ��� ���� ������ ��� ������ ����� ������� ������ �� �������
{
	int i;
	for (i = 0; i < r; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}


/*....ex3.....*/
void Ex3()
{
	int r, c, i, j, count = 0;
	int **matrix;//����� �� ����� �������
	create_three_var *arr = NULL;//����� �� ����� ����� ���� �����
	three_list *head = NULL;//����� �� ����� ������ ������ �� �����
	printf("please enter number of rows and then number of columns:\n");
	scanf(" %d %d", &r, &c);//����� ������� �� ���� ������ �������� �� �������
	matrix = DynamicMatrix(r, c);//����� ���� ������ �������� �������� ����� ������ �������, �� ������ ��������� ���� ������ �������
	printf("please enter the values of the matrix:\n");
	for (i = 0; i < r; i++)//����� ����� ������� ��������
	{
		for (j = 0; j < c; j++)
		{
			printf("for index [%d][%d]:", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	printf("the matrix is:\n");
	printMatrix(matrix, r, c);//����� ���� ������ ������� ������� ������� �������� �������� ������ �� ������� ������

	count = createArrayAndList(matrix, r, c,&arr,&head);//����� �������� �� ������� ����� ������� ������� ��� �� ���� ������ �������� �� ������ �������� ������ ������� ��� �� ��� ����� ����� ���������, �������� ����� �� ����� �� ���� ������ ������ ���������
	
	printf("the data in the array is:");
	for (i = 0; i < count; i++)//����� ���� ������ ������
	{
		printf("\n index [%d][%d] is %d", arr[i].i, arr[i].j, arr[i].value);
	}
	printf("\n");
	printf("\nthe data in the list is:\n");
	printList(head);//����� ������ ������ ������� �������� ������ �� ������ �������
	
	system("pause");
	free(arr);//����� �����
	freeMatrix(matrix, r);//����� ���� ����� ������� ������� �� ������� �������� ������ ������� ��������
	freeList(head);//����� ������ ������ ������� �������� ������ ����� �����
}

int createArrayAndList(int **matrix,int r,int c, create_three_var **arr, three_list **head)//�������� ����� �� �������� �� ����� ������ ������� �������� ��� �� ���� ������ �������� �� �������
{
	int i, j, count = 0;

	for (i = 0; i < r; i++)//����� ��� ����� ���� ����� ��������� �������
	{
		for (j = 0; j < c; j++)
		{
			if (matrix[i][j] == (i + j))
			{
				count++;//����� �� ��� ����� ����� �� ���� ������ ������ ����� ���������
			}
		}
	}
	
	(*arr) = createThreeArr(arr, matrix, r, c, count);//����� �������� �� ������� ������ ���� ������� ������� �� ������� ������ ����� �������� ������ �� ����� 
	(*head) = createThreeList(head, arr, count);//����� ����� ��������� �� ����� ������� ������� �������� ������ ������ �������

	return count;//����� ����� �������� ������
}


int createThreeArr(create_three_var **arr,int **matrix,int r, int c, int count)//�������� ����� �� ����� �� ���� ������� ������� ��������� �� ������� ������
{
	int i, j, k = 0;
	
	(*arr) = (create_three_var*)malloc(count * sizeof(create_three_var));//����� �� ����� ����� ������ �� ����� �� ��� ����� ����� �� �����
	
	for (i = 0; i < r; i++)//����� ������ �������� �����
	{
		for (j = 0; j < c; j++)
		{
			if (matrix[i][j] == i + j)
			{
				(*arr)[k] = createThree(i, j, matrix[i][j]);
				k++;
			}
		}
	}

	return (*arr);//����� ����� �����
}

create_three_var createThree(int i, int j, int value)//������� ������ �� ����� ����� �� ������ ��������
{
	create_three_var var1;
	var1.i = i;//������ ����
	var1.j = j;//����� �����
	var1.value = value;//��� ��� �� ������� ����� ����� ���������

	return var1;//����� ��� �����
}

int createThreeList(three_list **head, create_three_var **arr, int count)//�������� ����� �� ����� ��� �������� �� ����� ������� �������
{
	int k = 0;
	three_list *temp = NULL;
	//����� ������ ������� �� �� ����� �� �����
	for (k = 0; k < count; k++)
	{
		temp = (three_list*)malloc(sizeof(three_list)); 
		temp->data = (*arr)[k];
		temp->next = *head;
		*head = temp;
	}
	return (*head);//����� ������ ������ �������
}


void printListEx3(three_list *head)//������� ������ �� ������ ������ ������� ������� ����
{
	while (head != NULL)
	{
		printf(" [%d,%d,%d]->", head->data.i,head->data.i,head->data.value);
		head = head->next;
	}
	printf("  NULL\n");
}

void freeListEx3(three_list *head)//������� ������ �� ������ ������ ������� ������ ����� �����
{
	three_list *temp;
	while (head != NULL)
	{
	temp = head;
	head = temp->next;
	free(temp);
	}
}


/*....Ex4....*/
void Ex4() 
{
	list *head_even = NULL;//����� �� ����� ������ ������� ����� �� ������ ������ ��� ����� ���� ����� �� ������ ��� ������ ������� �������
	list *head_odd = NULL;//����� �� ����� ������ ��� �����

	head_even = buildOriginalList();//����� �� ����� ������ �������
	printf("Original list:");
	printList(head_even);//����� ������ ������ ������� ������� �������� ������ ����

	head_odd = createList(&head_even);//����� ������ �� ������ ������� �������� ������ ����� �� ������ �� ������ ������� ������� �� �� ��� ������, ������ ��� ����� ���� ������ 

	printf("Even list:");
	printList(head_even);//����� ������ ������ ������ �������� ������ �� ������ ������ ������
	printf("Odd list:");
	printList(head_odd);//����� ������ ������ ������ �������� ������ �� ������ ��� ����� ������

	system("pause");
	freeList(head_even);//����� ������ ������ ������ �������� ����� ����� �����
	freeList(head_odd);//����� ������ ������ ��� ����� �������� ����� ����� �����
}

list *buildOriginalList()//�������� ����� ������� ����� ������� ��� ����� ������, �������� ������ ����� �� ������ ������� ������ �������� ������
{
	int number = 0;
	list *head = NULL;
	list *tail = NULL;
	printf("please enter numbers, when finished enter a negative number\n");
	while (number >= 0)
	{
		scanf("%d", &number);
		if (number >= 0)
		{
			if (head == NULL)
			{
				head = (list*)malloc(sizeof(list));
				head->value = number;
				head->next = NULL;
				tail = head;
			}
			else
			{
				tail->next = (list*)malloc(sizeof(list));
				tail = tail->next;
				tail->value = number;
				tail->next = NULL;
			}
		}
	}
	return head;
}


list *createList(list **even_head)//�������� ����� �� ������ ������ ������� ������� ������ ������� ��� ������ ��� ����� ������ ������ ����� �� ������ ���� ����� ������� ������ �� ������ ���� �������� ����� ����
{
	list *odd_head = NULL;//����� �� ����� ���� ������ ��� �����
	list *odd_curr = NULL;//����� �� ����� ����� ����� �� ����
	list *even_curr = NULL;//����� �� ����� ����� ����� ����

	while ((*even_head != NULL)&&((*even_head)->value % 2 ==1))//����� ��� ����� ������ ������� ������ ������� ����� ���� ���� ����, �� �� ���� ��� ����� ����� ����� ��� ��� ����� ��� ���� ���� ���� ���� ��� ���� �������� ������ ���� ������ ��� ����� ����� ��� ���� ���� �������� ������ ���� ������� �������
	{
		list *temp = *even_head;
		*even_head = (*even_head)->next;
		odd_curr = Insert(&odd_head, &odd_curr, temp->value);
		Delete(temp);
		temp->next = NULL;
	}

	even_curr = *even_head;

	while ((even_curr != NULL) && (even_curr->next != NULL))//���� �� ������ �������, ����� ������ �� ����� ����� ������,����� ������� �� �����, �� ���� �� ���� ���� �������� ������ ���� ������ �� ����� �� �� ��� ������ ����� ��� �������� ����� ���� ������� �������
	{
		if (even_curr->next->value % 2 == 0)
		{
			even_curr = even_curr->next;
		}
		else
		{
			list *temp = even_curr->next;
			even_curr->next = temp->next;
			odd_curr = Insert(&odd_head, &odd_curr, temp->value);
			Delete(temp);
			temp->next = NULL;
		}
	}
	return odd_head;//����� ������ ������ ��� ����� �������� ������
}


//�������� ����� �� �������� �� ��� ������ ��� ����� ��� ������ �� ����� ��� ���� ������,���� ������ �����, ��� ���� �� ����� ��� ����
//�������� ����� �� ���� �� ����� ���� ����� ������ ���� ������ ������� ��� ����� �� �� ��� ������ ������ �� ������ ����� ������, ������ ����� ����� ��������� �����
list *Insert(list** head, list** tail, int value) 
{
	list *current = (list*)malloc(sizeof(list));
	current->value = value;
	current->next = NULL;

	if (*head == NULL)
	{
		current->next = (*head);
		*head = current;
		*tail = *head;
	}
	else
	{
		(*tail)->next = current;
		*tail = (*tail)->next;
	}
	return current;
}

int Delete(list *curr)//������� ������ �� ������ ����� ������ ��� ���� ����� ������ ���� 
{
	list *temp = NULL;
	temp = curr;
	curr = curr->next;
	free(temp);
	return 1;
}

void printList(list *head)//������� ������ �� ������ ���� ������ ������� ������� ����
{
	while (head != NULL)
	{
		printf(" [%d]->", head->value);
		head = head->next;
	}
	printf("  NULL\n");
}

void freeList(list *head)//������� ������ �� ������ ���� ������ ������� ������ ����� �����
{
	list *temp;
	while (head != NULL)
	{
		temp = head;
		head = temp->next;
		free(temp);
	}
}

/*....Ex5....*/
void Ex5()
{
	list *head_even2 = NULL;//����� �� ����� ������ ������� ����� �� ������ ������ ��� ����� ���� ������ �� ������
	list *head_odd2 = NULL;//����� �� ����� ������ ������� ��� �����

	head_even2 = buildOriginalList();//����� �� ����� ������ �������
	printf("Original list:");
	printList(head_even2);//����� ������ ������ ������� ������� �������� ������ ����

	head_odd2 = createList2(&head_even2);//����� ������ �� ������ ������� �������� ������ ����� �� ������ �� ������ ������� ������� �� �� ��� ������, ������ ��� ����� ���� ������

	printf("Even list:");
	printList(head_even2);//����� ������ ������ ������ �������� ������ �� ������ ������ ������
	printf("Odd list:");
	printList(head_odd2);//����� ������ ������ ������ �������� ������ �� ������ ��� ����� ������

	system("pause");
	freeList(head_even2);//����� ������ ������ ������ �������� ����� ����� �����
	freeList(head_odd2);//����� ������ ������ ��� ����� �������� ����� ����� �����
}

list *createList2(list **even_head)//�������� ����� �� ������ ������ ������� ������� ������ �� ������ ������� ������� ������ �� ����� ������ ���� ������ ������ �� ����� �� ������ ����
{
	list *odd_head = NULL;//����� �� ����� ���� ������ ��� �����
	list *odd_curr = NULL;//����� �� ����� ����� ����� �� ����
	list *even_curr = NULL;//����� �� ����� ����� ����� ����

	while ((*even_head != NULL) && ((*even_head)->value % 2 == 1))//����� ��� ����� ������ ������� ������ ������� ����� ���� ���� ����, �� �� ���� ��� ����� ����� ����� ��� ��� ����� ��� ���� ���� ���� ���� ��� ���� ���� ������ ��� �����
	{
		list *temp = *even_head;
		*even_head = (*even_head)->next;
		temp->next = NULL;
		if (odd_head == NULL)
		{
			temp->next = (odd_head);
			odd_head = temp;
			odd_curr = odd_head;
		}
		else
		{
			(odd_curr)->next = temp;
			odd_curr = (odd_curr)->next;
		}
	}

	even_curr = *even_head;

	while ((even_curr != NULL) && (even_curr->next != NULL))//���� �� ������ ������� �������, ����� ������ �� ����� ����� ������,����� ������� �� �����, �� ���� �� ���� ������ ������� ������� ������� ����� �� ����� �� �� ��� ����� ������� ������� �������
	{
		if (even_curr->next->value % 2 == 0)
		{
			even_curr = even_curr->next;
		}
		else
		{
			list *temp = even_curr->next;
			even_curr->next = temp->next;
			if (odd_head == NULL)
			{
				temp->next = (odd_head);
				odd_head = temp;
				odd_curr = odd_head;
			}
			else
			{
				(odd_curr)->next = temp;
				odd_curr = (odd_curr)->next;
			}
			temp->next = NULL;
		}
	}
	return odd_head;//����� ������ ������ ������� ��� �����
}