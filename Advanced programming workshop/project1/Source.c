
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
	scanf("%d", &n);//סריקה מהמשתמש את גודל של המשתנה שהוא גודל המערך
	unsigned int *p = powerArray(n);//שליחת הנתון הנקלט לפונקציה שתחשב את איברי המערך
	array_print(p, n);//שליחת מצביע למערך וגודלו לפונקצית הדפסה

	system("pause");
	free(p);
}

unsigned int powerArray(int n)//הפונקציה מקבלת מספר שלם, שהוא יהיה גודל המערך, ומחשבת את איברי המערך עפ"י החישוב של 2 בחזקת שארית החלוקה של האינדקס ב32
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

void array_print(unsigned int *arr, int n)//פונקציה המקבלת מצביע למערך וגודלו ומדפיסה את המערך 
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
	for (i = 0; i < M; i++)//Aקליטת ערכים למטריצה
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &matrixA[i][j]);
		}
	}

	printf("Type in values for matrix B with %d rows and %d colls\n", N, P);
	for (i = 0; i < N; i++)//B קליטת ערכים למטריצה
	{
		for (j = 0; j < P; j++)
		{
			scanf("%d", &matrixB[i][j]);
		}
	}

	matrixC = DynamicMatrix(M, P);//שליחת הגדלים של המטריצה לפונקציה שתבנה את המטריצה הדינאמית
	matrixC = matrixMultiplication(matrixA, matrixB, matrixC);//שליחת המטריצות לפונקציה שתחשב את הכפל בינהן
	
	printf("matrix A is:\n");//A הדפסת מטריצה
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%6d", matrixA[i][j]);
		}
		printf("\n");
	}
	printf("matrix B is:\n");//B הדפסת מטריצה
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < P; j++)
		{
			printf("%6d", matrixB[i][j]);
		}
		printf("\n");
	}
	printf("matrix c is:\n");
	printMatrix(matrixC, M, P);//C הדפסת מטריצת הכפל
	
	system("pause");
	freeMatrix(matrixC, M);//שחרור זכרון מטריצה דינאמית בעזרת פונקציה מתאימה
}

int **DynamicMatrix(int r, int c)//פונקציה הבונה מטריצה דינאמית
{
	int i;
	int **matrix = (int**)calloc(r , sizeof(int*));
	for (i = 0; i < r; i++)
	{
		matrix[i] = (int*)calloc(c , sizeof(int));
	}
	return matrix;
}

int **matrixMultiplication(int matrixA[M][N], int matrixB[N][P], int **matrixC)//פונקציה המקבלת את שתי המטריצות ומחשבת את הכפל בניהן, הפונקציה מחזירה את המצביע למטריצת הכפל
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

void printMatrix(int **matrix, int r, int c)//פונקציה המקבלת את המצביע למטריצה ואת מספר העמודות והשורות של המטריצה,הפונקציה מיועדת להדפסת מטריצות
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

void freeMatrix(int **matrix, int r)//פונקציה המקבלת את המצביע למטריצה ואת מספר השורות שלה ומבצעת שחרור לזיכרון דינאמי של המטריצה
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
	int **matrix;//הצהרה על מצביע למטריצה
	create_three_var *arr = NULL;//הצהרה על מצביע למערך מסוג שלשות
	three_list *head = NULL;//הצהרה על מצביע לרשימה מקושרת של שלשות
	printf("please enter number of rows and then number of columns:\n");
	scanf(" %d %d", &r, &c);//קליטה מהמשתמש את מספר השורות והעמודות של המטריצה
	matrix = DynamicMatrix(r, c);//שליחת מספר השורות והעמודות לפונקציה הבונה מטריצה דינאמית, מה שיוחזר מהפונקציה יכנס למצביע למטריצה
	printf("please enter the values of the matrix:\n");
	for (i = 0; i < r; i++)//קליטת ערכים למטריצה הדינאמית
	{
		for (j = 0; j < c; j++)
		{
			printf("for index [%d][%d]:", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	printf("the matrix is:\n");
	printMatrix(matrix, r, c);//שליחת מספר השורות העמודות והמצביע למטריצה הדינאמית לפונקציה שתדפיס את המטריצה שנקלטה

	count = createArrayAndList(matrix, r, c,&arr,&head);//שליחת המבציעים של המטריצה המערך והרשימה המקושרת יחד עם מספר השורות והעמודות של המריצה לפונקציה שתבדוק במטריצה האם יש ערך השווה לסכום האינדקסים, הפונקציה תחזיר את המונה של מספר הערכים השווים לאינדקסים
	
	printf("the data in the array is:");
	for (i = 0; i < count; i++)//הדפסת מערך השלשות שהתקבל
	{
		printf("\n index [%d][%d] is %d", arr[i].i, arr[i].j, arr[i].value);
	}
	printf("\n");
	printf("\nthe data in the list is:\n");
	printList(head);//שליחת המצביע לרשימה המקושרת לפונקציה שתדפיס את הרשימה המקושרת
	
	system("pause");
	free(arr);//שחרור המערך
	freeMatrix(matrix, r);//שליחת מספר שורות המטריצה והמצביע של המטריצה לפונקציה לשחרור המטריצה הדינאמית
	freeList(head);//שליחת המצביע לרשימה המקושרת לפונקציה שמבצעת שחרור זכרון
}

int createArrayAndList(int **matrix,int r,int c, create_three_var **arr, three_list **head)//הפונקציה מקבלת את המצביעים של המערך הרשימה המקושרת והמטריצה יחד עם מספר השורות והעמודות של המטריצה
{
	int i, j, count = 0;

	for (i = 0; i < r; i++)//ספירה כמה ערכים שוים לסכום האינדקסים במטריצה
	{
		for (j = 0; j < c; j++)
		{
			if (matrix[i][j] == (i + j))
			{
				count++;//משתנה זה הוא המונה המכיל את כמות הערכים השווים לסכום האינדקסים
			}
		}
	}
	
	(*arr) = createThreeArr(arr, matrix, r, c, count);//שליחת המצביעים של המטריצה והמערך מספר העמודות והשורות של המטריצה והמונה שנספר לפונקציה שתיצור את המערך 
	(*head) = createThreeList(head, arr, count);//שליחת המונה והמצביעים של המערך והרשימה המקושרת לפונקציה ליצירת הרשימה המקושרת

	return count;//החזרת המונה לפונקציה הראשית
}


int createThreeArr(create_three_var **arr,int **matrix,int r, int c, int count)//הפונקציה מקבלת את המונה את מספר העמודות והשורות והמצביעים של המטריצה והמערך
{
	int i, j, k = 0;
	
	(*arr) = (create_three_var*)malloc(count * sizeof(create_three_var));//יצירה של המערך באופן דינאמי של המערך עם תאי המערך בגודל של שלשות
	
	for (i = 0; i < r; i++)//הכנסת הערכים המתאימים למערך
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

	return (*arr);//החזרת מצביע למערך
}

create_three_var createThree(int i, int j, int value)//פונקציה היוצרת את איברי המערך עם הערכים המתאימים
{
	create_three_var var1;
	var1.i = i;//אינדקס שורה
	var1.j = j;//אידקס עמודה
	var1.value = value;//ערך בתא של המטריצה השווה לסכום האינדקסים

	return var1;//החזרת התא שנוצר
}

int createThreeList(three_list **head, create_three_var **arr, int count)//הפונקציה מקבלת את המונה ואת המצביעים של המערך והרשימה המקושרת
{
	int k = 0;
	three_list *temp = NULL;
	//יצירת הרשימה המקושרת על פי התאים של המערך
	for (k = 0; k < count; k++)
	{
		temp = (three_list*)malloc(sizeof(three_list)); 
		temp->data = (*arr)[k];
		temp->next = *head;
		*head = temp;
	}
	return (*head);//החזרת המצביע לרשימה המקושרת
}


void printListEx3(three_list *head)//פונקציה המקבלת את המצביע לרשימה המקושרת ומדפיסה אותה
{
	while (head != NULL)
	{
		printf(" [%d,%d,%d]->", head->data.i,head->data.i,head->data.value);
		head = head->next;
	}
	printf("  NULL\n");
}

void freeListEx3(three_list *head)//פונקציה המקבלת את המצביע לרשימה המקושרת ומבצעת שחרור זכרון
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
	list *head_even = NULL;//הצהרה על מצביע לרשימה המקורית שישמש גם כמצביע לרשימה האי זוגית לאחר מחיקה של הערכים האי זוגיים מהרשימה המקורית
	list *head_odd = NULL;//הצהרה על מצביע לרשימה האי זוגית

	head_even = buildOriginalList();//קליטה של ערכים לרשימה המקורית
	printf("Original list:");
	printList(head_even);//שליחת המצביע לרשימה המקושרת המקורית לפונקציה שתדפיס אותה

	head_odd = createList(&head_even);//שליחת המצביע של הרשימה המקורית לפונקציה שתיצור רשימה של מספרים אי זוגיים מהרשימה המקורית על פי סדר הקליטה, הרשימה האי זוגית תכנס למצביע 

	printf("Even list:");
	printList(head_even);//שליחת המצביע לרשימה הזוגית לפונקציה שתדפיס את הרשימה הזוגית שנוצרה
	printf("Odd list:");
	printList(head_odd);//שליחת המצביע לרשימה הזוגית לפונקציה שתדפיס את הרשימה האי זוגית שנוצרה

	system("pause");
	freeList(head_even);//שליחת המצביע לרשימה הזוגית לפונקציה שתבצע שחרור זכרון
	freeList(head_odd);//שליחת המצביע לרשימה האי זוגית לפונקציה שתבצע שחרור זכרון
}

list *buildOriginalList()//הפונקציה קולטת מהמשתמש ערכים ומרכיבה מהם רשימה מקושרת, הפונקציה מחזירה מצביע של הרשימה המקושרת שנקלטה לפונקציה הראשית
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


list *createList(list **even_head)//הפונקציה מקבלת את המצביע לרשימה המקושרת המקורית ויוצרת מהערכים האי זוגיים שבה רשימה מקושרת שמכילה ערכים אי זוגיים בלבד בעזרת פונקציה ושולחת את הערכים האלו לפונקציה שתמחק אותם
{
	list *odd_head = NULL;//הצהרה על מצביע לראש הרשימה האי זוגית
	list *odd_curr = NULL;//הצהרה על מצביע לאיבר נוכחי אי זוגי
	list *even_curr = NULL;//הצהרה על מצביע לאיבר נוכחי זוגי

	while ((*even_head != NULL)&&((*even_head)->value % 2 ==1))//בדיקה האם האיבר הראשון שהמצביע לרשימה הנוכחית מצביע עליו אינו זוגי, אם לא זוגי הוא ממשיך לאיבר הזוגי הבא ואת האיבר האי זוגי שהיה עליו קודם הוא שולח לפונקציה שתכניס אותו לרשימה האי זוגית ולאחר מכן שולח אותו לפונקציה שתמחוק אותו מהרשימה המקורית
	{
		list *temp = *even_head;
		*even_head = (*even_head)->next;
		odd_curr = Insert(&odd_head, &odd_curr, temp->value);
		Delete(temp);
		temp->next = NULL;
	}

	even_curr = *even_head;

	while ((even_curr != NULL) && (even_curr->next != NULL))//מעבר על הרשימה המקורית, בעזרת המצביע של האיבר הזוגי הנוכחי,בדיקה למספרים אי זוגים, כל מספר אי זוגי נשלח לפונקציה שתוסיף אותו לרשימה אי זוגית על פי סדר וקליטה ולאחר מכן לפונקציה שתמחק אותו מהרשימה המקורית
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
	return odd_head;//החזרת המצביע לרשימה האי זוגית לפונקציה הראשית
}


//הפונקציה מקבלת את המצביעים של ראש הרשימה האי זוגית ואת המצביע של האיבר האי זוגי הנוכחי,שהוא האחרון שנמצא, ואת הערך של המספר האי זוגי
//הפונקציה תוסיף את הערך של האיבר שהיא קיבלה ותוסיף אותו לרשימה המקושרת האי זוגית על פי סדר הקליטה ותחזיר את המצביע לאיבר הנוכחי, האחרון שנמצא ונוסף לרשימההאי זוגית
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

int Delete(list *curr)//פונקציה המקבלת את המצביע לאיבר הנוכחי האי זוגי שנמצא ומוחקת אותו 
{
	list *temp = NULL;
	temp = curr;
	curr = curr->next;
	free(temp);
	return 1;
}

void printList(list *head)//פונקציה המקבלת את המצביע לראש הרשימה המקושרת ומדפיסה אותה
{
	while (head != NULL)
	{
		printf(" [%d]->", head->value);
		head = head->next;
	}
	printf("  NULL\n");
}

void freeList(list *head)//פונקציה המקבלת את המצביע לראש הרשימה המקושרת ומבצעת שחרור זכרון
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
	list *head_even2 = NULL;//הצהרה על מצביע לרשימה המקורית שישמש גם כמצביע לרשימה האי זוגית לאחר הפיצול של הערכים
	list *head_odd2 = NULL;//הצהרה על מצביע לרשימה המקושרת האי זוגית

	head_even2 = buildOriginalList();//קליטה של ערכים לרשימה המקורית
	printf("Original list:");
	printList(head_even2);//שליחת המצביע לרשימה המקושרת המקורית לפונקציה שתדפיס אותה

	head_odd2 = createList2(&head_even2);//שליחת המצביע של הרשימה המקורית לפונקציה שתיצור רשימה של מספרים אי זוגיים מהרשימה המקורית על פי סדר הקליטה, הרשימה האי זוגית תכנס למצביע

	printf("Even list:");
	printList(head_even2);//שליחת המצביע לרשימה הזוגית לפונקציה שתדפיס את הרשימה הזוגית שנוצרה
	printf("Odd list:");
	printList(head_odd2);//שליחת המצביע לרשימה הזוגית לפונקציה שתדפיס את הרשימה האי זוגית שנוצרה

	system("pause");
	freeList(head_even2);//שליחת המצביע לרשימה הזוגית לפונקציה שתבצע שחרור זכרון
	freeList(head_odd2);//שליחת המצביע לרשימה האי זוגית לפונקציה שתבצע שחרור זכרון
}

list *createList2(list **even_head)//הפונקציה מקבלת את המצביע לרשימה המקושרת המקורית ומפצלת את הערכים שברשימה המקורית לרשימה של ערכים זוגיים בלבד ורשימה מקושרת של ערכים אי זוגיים בלבד
{
	list *odd_head = NULL;//הצהרה על מצביע לראש הרשימה האי זוגית
	list *odd_curr = NULL;//הצהרה על מצביע לאיבר נוכחי אי זוגי
	list *even_curr = NULL;//הצהרה על מצביע לאיבר נוכחי זוגי

	while ((*even_head != NULL) && ((*even_head)->value % 2 == 1))//בדיקה האם האיבר הראשון שהמצביע לרשימה הנוכחית מצביע עליו אינו זוגי, אם לא זוגי הוא ממשיך לאיבר הזוגי הבא ואת האיבר האי זוגי שהיה עליו קודם הוא מפצל אותו לרשימה האי זוגית
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

	while ((even_curr != NULL) && (even_curr->next != NULL))//מעבר על הרשימה המקושרת המקורית, בעזרת המצביע של האיבר הזוגי הנוכחי,בדיקה למספרים אי זוגים, כל מספר אי זוגי מפצלים מהרשימה המקורית ויוצרים רשימה אי זוגית על פי סדר קליטת האיברים מהרשימה המקורית
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
	return odd_head;//החזרת המצביע לרשימה המקושרת האי זוגית
}