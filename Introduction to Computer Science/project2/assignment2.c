#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();
void Ex6();

/* Declarations of other functions */

int evenNumber(int numOfEven);
int max_num(int n);
int even_or_odd(int n);
int add_one(int n);
int series(int n);
int function(int n, int dig);
/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
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
		} while (all_Ex_in_loop && select);
		return 0;
}

/*.............................*/
void Ex1()
{
	printf("the number of even numbers is %d\n", evenNumber(0));
	system("pause");
}

int evenNumber(int numOfEven)//äôåðö÷éä áåã÷ú ëîä îñôøéí æåâééí ð÷ìèå åîçæéøä àú ëîåú äîñôøéí äæåâééí 
{
	int number;
	printf("please enter numbers, when finish enter the number : -1\n");
	scanf("%d",&number);
	if (number ==-1)
	{
		return numOfEven;
	}
	else
	{
		if (number % 2 == 0)
		{
			numOfEven++;
		}
		return evenNumber(numOfEven);
	}
}

/*......................................*/

/*.......................................*/
void Ex2()
{
	int n;
	printf("please enter a number\n");
	scanf("%d", &n);
	printf("the max number is %d\n", max_num(n));
	system("pause");
}

int max_num(int n)//äôåð÷öéä î÷áìú îñôø èáòé ëìùäåà åîçæéøä àú äñôøä äî÷ñéîìéú
{
	int biggest_num, devided_num;

	if (n <= 0)
	{
		return n;
	}
	else
	{
		devided_num = n % 10;
		biggest_num = max_num(n / 10);
		if (devided_num > biggest_num)
		{
			biggest_num = devided_num;
		}
		if (biggest_num == 9)
		{
			return biggest_num;
		}
	}
	return biggest_num;
}
/*..........................................*/

/*..........................................*/
void Ex3()
{
	int n;
	printf("please enter a number\n");
	scanf("%d", &n);
	printf(" %d\n", even_or_odd(n));
	system("pause");
}

int even_or_odd(int n)//äôåð÷öéä î÷áìú îñôø èáòé ñåëîú àú äñôøåú ùìå îçæéøä 1 àí äñëåí àé æåâé å0 àí äñëåí æåâé
{
	int num;
	if (n > 0)
	{
		num = ((n % 10) + even_or_odd(n / 10));
		if (num % 2 == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}
/*..............................................*/

/*.............................................*/
void Ex4()
{
	int n;
	printf("please enter a positive number\n");
	scanf("%d", &n);
	printf(" %d\n", add_one(n));
	system("pause");
}

int add_one(int n)//äôåð÷öéä îåñéôä 1 ìëì îñôø áñôøä äîú÷áìú, àí äôåð÷öéä î÷áìú 9 äéà úçæéø 0
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		if (n <= 9)
		{
			return ((n + 1) % 10);
		}
	}
	return 10 * add_one(n / 10) + (((n % 10) + 1) % 10);
}
/*......................................................*/

/*......................................................*/
void Ex5()
{
	int n;
	printf("please enter a number bigger then 9\n");
	scanf("%d", &n);
	printf(" %d\n", series(n));
	system("pause");
}

int series(int n)//äôåð÷öéä î÷áìú îñôø åáåã÷ú àí äñãø ùì äîñôøéí òåìä îçæéøä 1, àí äñãø ùì äîéñôøéí éåøã îçæéøä -1, àí ìà æä åìà æä îçæéøä 0
{
	if (n < 100)
	{
		if (n % 10 < (n / 10) % 10)
		{
			return -1;
		}
		if (n % 10 > (n / 10) % 10)
		{
			return 1;
		}
		return 0;
	}
	if ((n % 10 < (n / 10) % 10) && (series(n / 10) == -1))
	{
		return -1;
	}
	else if ((n % 10 > (n / 10) % 10) && (series(n / 10) == 1))//îñúîñê òì äúðàé ìîòìä 
	{
		return 1;
	}
	else {
		return 0;
	}
}
/*......................................................*/

/*.....................................................*/
//ex6().................................................
void Ex6()
{
	int n, dig;
	printf("please enter a number : n\n");
	scanf("%d", &n);
	printf("please enter dig number : dig\n");
	scanf("%d", &dig);
	printf(" %d\n", function(n, dig));
	system("pause");
}

int function(int n, int dig)
{
	int num = n % 10;
	if (n > 0)
	{
		if (num == dig)
		{
			return function((n / 10), dig);
		}
		else
		{
			return (10 * function((n / 10), dig)) + ((num % 10) % 10);
		}
	}
}
/*....................................................*/
