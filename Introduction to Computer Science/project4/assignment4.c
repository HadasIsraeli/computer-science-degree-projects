
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


/* Function declarations */
void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex41();
void Ex42();
void Ex5();
void Ex51();
void Ex52();
void Ex6();



/* Declarations of other functions */
int max_number(int arr[], int n);
int Subtracting_values(int *arr_A, int n, int *arr_B, int m, int d);
int *common_values_array(int *arr_A, int n, int *arr_B, int m, int *count);
int number_check_with_array(int *arr, int n);
int number_check_without_array(int *arr, int n);
int composition_1(int *arr_A, int *arr_B, int n);
int composition_2(int *arr_A, int *arr_B, int n);
int zeros_to_end_of_array(int *arr, int n);


int *input_array_dyn(int n);
void swap(int *v, int *u);
int split(int *a, int left, int right);
void quick_sort(int *x, int first, int last);
int bin_search_last(int key, int *a, int n);
void array_print(int* a, int n);



//תבנית עבודה
int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n (Once - enter 0, cyclically - enter other number) ");
		if (scanf("%d", &all_Ex_in_loop) == 1)
			do
			{
				for (i = 1; i <= 6; i++)
					printf("Ex%d--->%d\n", i, i);
				printf("EXIT-->0\n");
				do {
					select = 0;
					printf("please select 0-6 : ");
					scanf("%d", &select);
				} while ((select < 0) || (select > 6));
				switch (select)
				{
				case 1: Ex1(); break;
				case 2: Ex2(); break;
				case 3: Ex3(); break;
				case 4: Ex4(); break;
				case 5: Ex5(); break;
				case 6: Ex6(); break;
				}
			} 
	while (all_Ex_in_loop && select);
	return 0;
	system("pause");
}



void Ex1()//פונקציה ראשית לסעיף 1, קולטת מערך שולחת אותו למפונקציה המחפשת את המספר הגדול במערך ומדפיסה את התשובה שהיא מקבלת חזרה 
{
	int n;
	printf("please enter the lenght of the array \n");
	scanf("%d", &n);
	int *arr = input_array_dyn(n);

	printf("the max number is lociated:\n arr[%d]\n", max_number(arr, n));
	free(arr);
	system("pause");
}

//ex 1
int max_number(int arr[], int n)//פונקציה המחזירה את מיקומו של הערך הגדול ביותר במערך המתקבל
{
	int high = n - 1, low = 0;
	int middle = (high - low) / 2 + low;

	if (arr[middle] > arr[middle + 1] && arr[middle] > arr[middle - 1])
	{
		return middle;
	}

	while (low < high)
	{
		if (arr[middle] > arr[middle + 1] && arr[middle] > arr[middle - 1])
		{
			return middle;
		}
		if (arr[middle] < arr[middle + 1])
		{
			low = middle + 1;
		}
		if (arr[middle] < arr[middle - 1])
		{
			high = middle - 1;
		}
		middle = (high - low) / 2 + low;
	}
	return middle;
}


void Ex2()//פונקציה ראשית לסעיף 2,קולטת 2 מערכים ואת גודל כל אחד מהם ואת הערך הרצוי שיתקבל מהחיסור שלהם, שולחת את הערכים הללו לפונקציה הבודקת אם החיסור בין ערכים במערך נותן את המספר הרצוי ומקבלת 1 אם קיימים ערכים שמקיימים את החיסור ו0 אם לא קיימים ערכים כאלו  
{
	int n, m, d;
	printf("please enter the lenght of array A: \n");
	scanf("%d", &n);
	int *arr_A = input_array_dyn(n);
	printf("please enter the lenght of array B: \n");
	scanf("%d", &m);
	int *arr_B = input_array_dyn(m);
	printf("please enter the difference d: \n");
	scanf("%d", &d);

	printf("the result is\n   %d\n", Subtracting_values(arr_A, n, arr_B, m, d));
	free(arr_A);
	free(arr_B);
	system("pause");
}

//ex2
int Subtracting_values(int *arr_A, int n, int *arr_B, int m, int d)//פונקציה המקבלת 2 מערכים וגודלם וערך רצוי,הפונקציה מחפשת האם חיסור בין ערכי המערכים נותן את המספר הרצוי 
{
	int i = 0;
	if (m < n)
	{
		quick_sort(arr_A, 0, n - 1);
		for (i = 0; i < n; i++)
		{
			if (bin_search_last((arr_B[i] + d), arr_A, n) != -1)
			{
				return 1;
			}
		}
	}
	else
	{
		quick_sort(arr_B, 0, m - 1);
		for (i = 0; i < m; i++)
		{
			if (bin_search_last((arr_A[i] - d), arr_B, m) != -1)
			{
				return 1;
			}
		}
	}
	
	return 0;
}


void Ex3()//הפונקציה קולטת 2 מערכים וגודלם ומגדירה מונה השווה לאפס , שולחת את שני המערכים גודלם והמונה לפונקציה הבודקת את הערכים המשותפים שלהם ומקבלת בחזרה את המערך עם הערכים המשותפים ומדפיסה אותו
{
	int n, m;
	int *count;
	printf("please enter the lenght of array A: \n");
	scanf("%d", &n);
	int *arr_A = input_array_dyn(n);
	printf("please enter the lenght of array B: \n");
	scanf("%d", &m);
	int *arr_B = input_array_dyn(m);

	int *arr_C = common_values_array(arr_A, n, arr_B, m, &count);
	printf("the new array with coomon values is:\n");
	array_print(arr_C, count);

	free(arr_A);
	free(arr_B);
	system("pause");
}

//ex3
int *common_values_array(int *arr_A, int n, int *arr_B, int m, int *count)//פונקציה המקבלת 2 מערכים וגודלם ומונה , הפונקציה בודקת מה הם הערכים הזהים בשני המערכים ושמה במערך נוסף את ערכים אלו בכמות הערכים המינימלית המופיעה באחד המערכים , הפונקציה תדפיס על המסך את גודל המערך לפי המונוה תחזיר את המערך עם הערכים המשותפים  
{
	int i = 0, j = 0;
	int counter = 0;
	int max = n;
	if (m > n)
	{
		max = m;
	}
	int *arr_C = (int*)malloc(0);
	
	quick_sort(arr_A, 0, n - 1);
	quick_sort(arr_B, 0, m - 1);

	while (max >= 0)
	{
		if (arr_A[i] == arr_B[j])
		{
			arr_C[counter] = arr_A[i];
			counter++;
			i++;
			j++;
		}
	
		else if (arr_A[i] < arr_B[j])
		{
			i++;
		}
		else //arr_A[i] > arr_B[j]
		{
			j++;
		}
		max--;
	}
	printf("the size of arr_C is : %d\n", counter);
	arr_C[counter] = '\0';
	*count = counter;
	return arr_C;
	free(arr_C);
}


void Ex4()//פונקציה בחירה בין סעיף א לסעיף ב של השאלה
{
	int select;
	printf("For 4a select 1, for 4b select 2\n");
	scanf("%d", &select);
	switch (select)
	{
		case 1: Ex41(); break;
		case 2: Ex42(); break;
		default: printf("Invalid choice\n");
	}
	system("pause");
}

void Ex41()//פונקציה לסעיף א, הפונקציה קולטת מערך וגודלו ושולחת אותם לפונקציה הבודקת את ערכי המערך הנקלט,אם הם בין 0 עד לגודל המערך פחות 1, הפונקציה תקבל תשובה חזרה מהפונקציה , 1 אם הערכים בתחום הרצוי ו0 אם לא 
{
	int n;
	printf("please enter the lenght of the array \n");
	scanf("%d", &n);
	int *arr = input_array_dyn(n);

	printf("are the numbers in the array are from 0 to n-1?\n no-0\n yes-1:\n the answer with array is: %d\n", number_check_with_array(arr, n));
	free(arr);
}

//ex4.1
int number_check_with_array(int *arr, int n)//פונקציה המקבלת מערך וגודלו, הפונקציה תבדוק האם ערכים המערך הם בתחום שבין 0 לגודל המערך פחות 1, הפונקציה תשתמש במערך עזר שגודלו זהה למערך המתקבל, במידה וקיים ערך במערך המתקבל הזהה למיקום הקיים במערך העזר, מערך העזר יכניס 1 במיקום זה, הפונקציה תבדוק האם כל הערכים במערך העזר הם שונים 1, אם כן תחזיר לפונקציה 0 אם לא תחזיר 1
{
	int i = 0, count = 0;
	int *counter = (int*)calloc(n, sizeof(int));
	
	for (i = 0; i < n; i++)
	{
		counter[arr[i]]++;
	}
	for (i = 0; i < n; i++)
	{
		if (counter[i] != 0)
		{
			count++;
		}
	}
	if (count == (n))
		{
			return 1;
		}
	else 
		{
			return 0;
		}
	free(counter);
}


void Ex42()//פונקציה לסעיף א, הפונקציה קולטת מערך וגודלו ושולחת אותם לפונקציה הבודקת את ערכי המערך הנקלט,אם הם בין 0 עד לגודל המערך פחות 1, הפונקציה תקבל תשובה חזרה מהפונקציה , 1 אם הערכים בתחום הרצוי ו0 אם לא 
{
	int n;
	printf("please enter the lenght of the array \n");
	scanf("%d", &n);
	int *arr = input_array_dyn(n);

	printf("are the numbers in the array are from 0 to n-1?\n no-0\n yes-1:\n the answer without array is: %d\n", number_check_without_array(arr, n));
	free(arr);
}

//ex4.2//פונקציה המקבלת מערך וגודלו, הפונקציה תבדוק ללא מערך עזר האם ערכי המערך קטנים מגודלו וגדולים ושווים ל0, אם כן הפונקציה תחזיר 1, אם לא תחזיר 0
int number_check_without_array(int *arr, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if ((arr[i] < n) && (arr[i] >= 0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}		
}


void Ex5()//פונקציה בחירה בין סעיף א לסעיף ב של השאלה
{
	int select;
	printf("For 5a select 1, for 5b select 2\n");
	scanf("%d", &select);
	switch (select)
	{
		case 1: Ex51(); break;
		case 2: Ex52(); break;
		default: printf("Invalid choice\n");
	}
	system("pause");
}

void Ex51()//הפונקציה קולטת שני מערכים ואת הגודל המשותף לשניהם, הפונקציה שולחת את שני המערכים ואת גודלם לפונקציה הבודקת האם המערכים בנויים מאותם ערכים
{
	int n;
	printf("please enter the lenght of the arrays: \n");
	scanf("%d", &n);
	printf("please enter array A:\n");
	int *arr_A = input_array_dyn(n);
	printf("please enter array B:\n");
	int *arr_B = input_array_dyn(n);

	printf("is array A is composition to array B?\n no-0\n yes-1:\n the answer composition_1 is: %d\n", composition_1(arr_A, arr_B, n));
	free(arr_A);
	free(arr_B);
}

//ex51
int composition_1(int *arr_A, int *arr_B, int n)//פונקציה המקקבלת שני מערכים וגודל המשותף לשניהם, הפונקציה תמיין את שני המערכים ותבדוק לאחר מיונם האם הערכים הם שונים באותו מקום בשני המערכים, אם כן שונים תחזיר 0 אם לא תחזיר 1
{
	int i = 0;
	quick_sort(arr_A, 0, n - 1);
	quick_sort(arr_B, 0, n - 1);

	for (i = 0; i < n; i++)
	{
		if (arr_A[i] != arr_B[i])
		{
			return 0;
		}
	}
		return 1;
}

void Ex52()//הפונקציה קולטת שני מערכים ואת הגודל המשותף לשניהם ותבדוק האם המערך הראשון הוא תמורה למערך השני, הפונקציה שולחת את שני המערכים ואת גודלם לפונקציה הבודקת האם המערכים בנויים מאותם ערכים
{
	int n;
	printf("please enter the lenght of the arrays: \n");
	scanf("%d", &n);
	printf("please enter array A\n");
	int *arr_A = input_array_dyn(n);
	printf("please enter array B\n");
	int *arr_B = input_array_dyn(n);

	printf("is array A is composition to array B?\n no-0\n yes-1:\n the answer composition_2 is: %d\n", composition_2(arr_A, arr_B, n));
	free(arr_A);
	free(arr_B);
}

//ex52
int composition_2(int *arr_A, int *arr_B, int n)//פונקציה המקבלת שני מערכים ואת הגודל המשותף לשניהם ובודקת האם המערך הראשון הוא תמורה למערך השני, הפונקציה מגדירה מערך בגודל 101 תאים מ0 עד 100, הפונקציה תבדוק את ערכי המערך הראשון ולפי הערך במערך תכניס 1 במיקום במערך העזר הזהה לערך במערך הנבדק, הפונקציה תחסר פחות 1 במערך העזר בעזרת המיקום השווה לערך המערך השני, לאחר מכן הפונקציה תבדוק האם במערך העזר כל ערכי המערך הם שונים מאפס  אם כן היא תחזיר 0 או לא היא תחזיר 1 
{
	int i = 0;
	int counter[101] = { 0 };
	quick_sort(arr_A, 0, n - 1);
	quick_sort(arr_B, 0, n - 1);

	for (i = 0; i < n; i++)
	{
		counter[arr_A[i]]++;
	}
	for (i = 0; i < n; i++)
	{
		counter[arr_B[i]]--;
	}
	for (i = 0; i < 101; i++)
	{
		if (counter[i] != 0)
		{
			return 0;
		}
	}
	return 1;
}



void Ex6()//פונקציה הקולטת מערך ואת גודלו, שולחת אותה לפונקציה המעבירה את כל האפסים המערך לסוף המערך, הפונקציה תדפיס את המערך החדש שהיא מקבלת
{
	int n;
	printf("please enter the lenght of the array \n");
	scanf("%d", &n);
	int *arr = input_array_dyn(n);
	arr = zeros_to_end_of_array(arr, n);
	printf("the new array is:\n");
	array_print(arr, n);
	free(arr);
	system("pause");
}

//ex6
int zeros_to_end_of_array(int *arr, int n)//פונקציה המקבלת מערך וגודלו, הפונקציה תבדוק את הערכים במערך המתקבל ואם הם שוים לאפס היא תעביר אותם לסוף המערך ותחזיר את המערך החדש 
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] != 0)
		{
			arr[count++] = arr[i];
		}
	}
	while (count < n)
	{
		arr[count++] = 0;
	}
	return arr;
}





int *input_array_dyn(int n)
{
	int i;
	int *a;
	a = (int *)malloc(n * sizeof(int));
	assert(a);
	// malloc() worked
	printf("enter the array of length %d\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", a + i);
	return a;
}

void swap(int *v, int *u)
{
	int temp;
	temp = *v;
	*v = *u;
	*u = temp;
}

int split(int *a, int left, int right)
{
	int i, last = left;
	if (left < right)
	{
		for (i = left + 1; i <= right; i++)
		{
			if (a[i] <= a[left])
			{
				swap(a + (++last), a + i);
			}
		}
		swap(a + left, a + last);
	}
	return last;
}

void quick_sort(int *x, int first, int last)
{
	int pos;
	if (first < last)
	{
		pos = split(x, first, last);
		quick_sort(x, first, pos - 1);
		quick_sort(x, pos + 1, last);
	}
}

int bin_search_last(int key, int *a, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key < a[mid])
			high = mid - 1;
		else
			if (key > a[mid])
				low = mid + 1;
			else //key=a[mid]
				if ((low == high) || (a[mid + 1] > key))
					return mid;
				else
					low = mid + 1;
	}
	return -1;
}

void array_print(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	}
