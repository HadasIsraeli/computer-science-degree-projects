/*
Assigned by:
Student1_Hadas_Israeli #ID207041443
Student2_Inbar_Israeli #ID205925290
*/


#include <stdio.h>
/* Function declarations */
void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();
void Ex6();

/* Declarations of other functions */

int middle_number(int num1, int num2, int num3);
int max_num(int n);
int	rain_days(int numDays);
int multiplie(int x, int y);
double function(double n, double x);
int Sum_Proper_Divisors(int n);
/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf_s("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 6; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-6 : ");
				scanf_s("%d", &select);
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
		} while (all_Ex_in_loop && select);
		return 0;
}

/*.............................*/
void Ex1()
{
	int num1, num2, num3;
	printf("please enter 3 numbers\n");
	scanf_s("%d %d %d", &num1, &num2, &num3);
	printf(" %d\n", middle_number(num1,num2, num3));
	system("pause");
}

int middle_number(int num1, int num2, int num3)//הפונקציה מקבלת שלושה מספרים ומחזירה את ערך המספר האמצעי
{
	if (num1 <= num2 && num2 <= num3)
	{
		return num2;
	}
	else if (num3 <= num2 && num2 <= num1)
	{
		return num2;
	}
	else if (num2 <= num1 && num1 <= num3)
	{
		return num1;
	}
	else if (num3 <= num1 && num1 <= num2)
	{
		return num1;
	}
	else
	{
		return num3;
	}
}
/*......................................*/

/*.............................*/
void Ex2()
{
	int b;
	printf("Please enter a number:\n ");
	scanf_s("%d", &b);
	printf("%d\n", max_num(b));
	system("pause");
}

int max_num(int n)//הפונקציה מקבלת מספר טבעי כלשהוא ומחזירה את הספרה המקסימלית 
{
	int biggest_num = 0;
	int devided_num = 0;
	int using_num = n;

	while (using_num != 0 && using_num < 1000000000)
	{
		devided_num = using_num % 10;
		if (devided_num >= biggest_num)
		{
			biggest_num = devided_num;
		}
		if (biggest_num == 9)
		{
			devided_num /= 0;
		}
		using_num /= 10;

	}
	return biggest_num;
}
/*......................................*/

/*.............................*/
void Ex3()
{
	int numDays;
	printf("Enter the number of days: \n");
	scanf_s("%d", &numDays);
	printf("%d\n", rain_days(numDays));
	system("pause");
}

int	rain_days(int numDays)//הפונקציה מקבלת את כמות הגשם שירד במשך מספר ימים ומחזירה את מספרו של היום הראשון שבו החל הרצף המקסימלי של ימי גשם
{
	int counter = 0;
	int maxDayCount = 0;
	int maxCount = 0;
	int RainAmount;
	int i;
	for (i = 1; i <= numDays; i++)
	{
		printf("Enter the amount of rain: \n");
		scanf_s("%d", &RainAmount);
		if (RainAmount > 0)
		{
			counter++;
		}
		else
		{
			if (counter > maxCount)
			{
				maxCount = counter;
				maxDayCount = i - counter;
			}
			counter = 0;
		}
	}
	if (counter > maxCount)
	{
		maxCount = counter;
		maxDayCount = i - counter;
	}
	return maxDayCount;
}

/*......................................*/


/*.............................*/
void Ex4()
{
	int x, y;
	printf("please enter two numbers:\n");
	scanf_s("%d%d", &x, &y);
	printf("the result is :%d\n", multiplie(x, y));
	system("pause");
}

int multiplie(int x, int y)//הפונקציה מקבלת ערך של 2 מספרים ומבצעת כפל ביניהם
{
	int i;
	int result = 0;

	if (x >= y)
	{
		if (y % 2 == 0)
		{
			x = x + x;
			for (i = 0; i < y / 2; i++)
			{

				result = result + x;
			}
		}
		else
		{
			for (i = 0; i < y; i++)
			{
				result = result + x;
			}
		}
	}
	else
	{
		if (x % 2 == 0)
		{
			y = y + y;
			for (i = 0; i < x / 2; i++)
			{
				result = result + y;
			}
		}
		else
		{
			for (i = 0; i < x; i++)
			{
				result = result + y;
			}
		}

	}

	return result;
}
/*......................................*/

/*.............................*/
void Ex5()
{
	double x, n;
	printf("please enter a natural number n\n");
	scanf_s("%lf", &n);
	printf("please enter any number x\n");
	scanf_s("%lf", &x);
	printf("the sum is: %lf", function(n, x));
	system("pause");
}

double function(double n, double x)//הפונקציה מקבלת מספר טבעי ומספר ממשי ומחשבת סכום. הפונקציה רצה בסדר גודל המספר הטבעי 
{
	double i, sum = 1, assembly = 1, k = 1, x1 = 1;
	for (i = 1; i <= n; i++)
	{
		x1 = (x*x)*x1;
		assembly = assembly * i;
		k = k * (-1);
		sum = sum + (k*(x1 / assembly));
	}
	return sum;
}
/*......................................*/


/*.............................*/
void Ex6()
{
	int i, n, SumDivs1;
	printf("please enter a number:\n");
	scanf_s("%d", &n);
	for (i = 1; i <= n; i++)
	{
		SumDivs1 = Sum_Proper_Divisors(i);
		if (i == Sum_Proper_Divisors(SumDivs1) && SumDivs1 > i)
		{
			printf("(%d,%d)\n", i, SumDivs1);
		}
	}
	system("pause");
}

int Sum_Proper_Divisors(int n)//הפונקציה מקבלת מספר ובודקת בטווח המספר המתקבל את המספרים הידידים הקיימים
{
	int sum = 1, i;
	if (n == 1)
		return 1;
	for (i = 2; i * i < n; i++) {
		if (n % i == 0) {
			sum += i + (n / i);
		}
		if (i * i == n) {
			sum += i;
		}
	}
	return sum;
}

/*......................................*/

