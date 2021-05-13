
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Function declarations */
void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();

/* Declarations of other functions */
//Ex1 functions
char** split(char *str, char letter, int *size);
void freeArray(char **array, int size);
void printArray(char **array, int n);
//Ex2 functions
char* clearDigitsAndSpaces(char *str);
//Ex3 functions
void createFile(char *file);
char commonestLetter(char* filename);
char* inputStrings();
//Ex4 functions
void decode(char *str);
//Ex5 functions
void memoryReport(char *declarition, char *file_name);
void printtFileTxt(char *name_of_file);

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
/* -------------------- */

/* Function definitions */

/*....ex1....*/
void Ex1()
{
	int size = 0, i = 0, j = 0;
	char *str[100], letter, **array;
	printf("\nEnter the string and press ENTER to check (max 100): ");
	getchar();
	fgets(str, 100, stdin);
	printf("\nEnter the character for check (only small letters): ");
	scanf("%c", &letter);
	array = split(str, letter, &size);
	if (array == NULL)
	{
		printf("there are no characters like %d", letter);
		free(str);
		return 0;
	}
	printArray(array, size);
	printf("The size of the array of strings (passed by reference from the function) is: %d\n", size);
	freeArray(array, size);
	system("pause");
}

//פונקציה המקבלת אות קטנה, מחרוזת ומשתנה סייז השייך למחרוזת החדשה שתיווצר. הפונקציה בודקת האם במחרוזת ישנה מילה המתחילה עם האות הקטנה או אותה אות רק גדולה
//אם ישנה מילה אשר מתחילה באות זו היא מכניסה אותה למערך דינאמי דו מימדי של מחרוזות ועוברת למילה הבאה. הפונקציה מחזירה, את הכתובת ע"י מצביע סייז, את כמות המילים, כמות השורות, שנמצאות במערך המחרוזות 
char** split(char *str, char letter, int *size)
{
	char **array, upper_letter = toupper(letter);
	int count = 0, i = 0, j = 0, k = 0, counter = 0;

	if (str[0] == letter || str[0] == upper_letter)
	{
		count++;
	}
	for (i = 1; str[i] != '\0'; i++)
	{
		if ((str[i] == letter || str[i] == upper_letter)&&(str[i-1]==' '))
		{
			count++;
		}
	}
	if (count == 0)
	{
		printf("\nThere is no suitable data. Please reinput the string.\n");
		return NULL;
	}
	*size = count;
	array = (char**)malloc(count * sizeof(char*));

	for (k = 0; k < count; k++)
	{
		i = 0;
		if (str[0] == letter || str[0] == upper_letter)
		{
			i = 0;	
			counter = 1;
			while ((str[i + 1] != ' ') && (str[i + 1] != '\n') && (str[i + 1] != '\0'))
			{
				counter++;
				i++;
			}
			array[0] = (char*)malloc((counter+1) * sizeof(char));
			for (j = 0; j < counter; j++)
			{
				array[0][j] = str[j];
			}
			array[0][counter] = '\0';
			counter = 0;
			k++;
			i = 1;
		}
		while ((str[i + 1] != '\n') || (str[i + 1] != '\0'))
		{
			if ((str[i] == letter || str[i] == upper_letter) && (str[i - 1] == ' '))
			{
				j = i;
				counter++;
				while ((str[j + 1] != ' ') && (str[j + 1] != '\n') && (str[j + 1] != '\0'))
				{
					counter++;
					j++;
				}
				array[k] = (char*)malloc((counter+1) * sizeof(char));
				for (j = 0; j < counter; j++)
				{
					array[k][j] = str[i];
					i++;
				}
				array[k][counter] = '\0';
				k++;
				counter = 0;
			}
			i++;
			if ((str[i] == '\0')||(str[i] == '\n'))
			{
				return array;
			}
		}
	}
}

//פונקציה לשחרור זכרון של המערך הדינאמי הדו מיימדי של המחרוזות
void freeArray(char **array, int size)//פונקציה המקבלת את המצביע למערך ואת מספר השורות שלו ומבצעת שחרור לזיכרון דינאמי שלו
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(array[i]);
	}
	free(array);
}

//פונקציה להדפסת המחרוזות במערך הדו מימדי
void printArray(char **array, int n)
{
	int i;
	printf("\nThe array of suitable strings is:\n");
	for (i = 0; i < n; i++)
	{
		puts(array[i]);
	}
}

/*....ex2....*/
void Ex2()
{
	char str[100], *new_str;
	printf("\nEnter the string and press ENTER to delete all spaces and digits (max 100): ");
	getchar();
	fgets(str, 100, stdin);
	new_str = clearDigitsAndSpaces(str);
	printf("\nThe output string is: ");
	printf("%s\n", new_str);
	system("pause");
	//free(str);
	//free(new_str);
}

//פונקציה המקבלת מחרוזת ומנקה ממנה את כל הרווחים והמספרים שיש בה ומחזירה את המחרוזת החדשה
char* clearDigitsAndSpaces(char *str)
{
	int i = 0, j = 0, count = 0, size = 0;
	char *new_str;
	size = strlen(str);
	for (i = 0; i < (size-1); i++)
	{
		if ((str[i] != ' ') && (isdigit(str[i]) == 0))
		{
			count++;
		}
	}
	new_str = (char*)malloc((count) * sizeof(char));
	for (i = 0; i < (size-1); i++)
	{
		if ((str[i] != ' ') && (isdigit(str[i]) == 0))
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[count] = '\0';
	return new_str;
}

/*....ex3....*/
void Ex3()
{
	char *file_name="input.txt";//הצהרה על מחרוזת המכילה את שם הקובץ כמבוקש בנתוני השאלה
	char character;
	createFile(file_name);
	character = commonestLetter(file_name);
	if (character)
	{
		printf("The most common letter is %c\n", character);
	}
	else
	{
		printf("there are no letters in the file %s\n",file_name);
	}
	system("pause");
}

//פונקציה המקבלת מחרוזת שהיא שם של קובץ, פותחת קובץ בשם זה ומכניסה לתוכו טקסט
void createFile(char *file)
{
	char *string;
	FILE *f = fopen(file, "w");
	if (f == NULL)
	{
		printf("failed creating a new file named %s \n",file);
		return;
	}
	printf("the file %s is now open. please enter a string: \n",file);
	string = inputStrings();
	fprintf(f, "%s\n", string);
	printf("the file %s is now close\n",file);
	fclose(f);
}

//פונקציה המקבלת מחרוזת שהיא שם של קובץ ומחפשת בתוך הטקסט של הקובץ את האות שמופיעה הכי הרבה ותחזיר אותה לפונקציה
char commonestLetter(char* file_name)
{
	FILE* f = fopen(file_name, "r"); 
	int counter[26] = { 0 }; 
	int i, character, most_common = 0;
	char letter;
	if (f == NULL)
	{
		printf("failed creating a new file named %s \n", file_name);
		return;
	}
	while ((character = fgetc(f)) != EOF)  
	{
		if (character >= 'a' && character <= 'z')
			counter[character - 'a']++;

		if (character >= 'A' && character <= 'Z')
			counter[character - 'A']++;
	}
	fclose(f);
	for (i = 0; i < 26; i++)
	{
		if ((counter[i] > most_common) || (counter[i] == most_common) && (counter[i] != 0)) 
		{
			most_common = counter[i];
			letter = i + 'A';
		}
	}
	if (most_common != 0)
	{
		return letter;
	}
	else
	{
		return NULL;
	}
}

//פונקציה לקליטת מחרוזת והחזרת מחרוזת דינאמית, קולטת מהמשתמש את המחרוזת מחשב את גודל המחרוזת ומעתיק אותה למחרוזת חדשה על מנת שהגודל יהיה לא יותר ממה שצריך
char* inputStrings()
{
	char str[100], *string;
	rewind(stdin);
	gets(str);
	string = (char*)malloc((strlen(str)) + 1);
	strcpy(string, str);
	return string;
}


/*....ex4....*/
void Ex4()
{
	char string[]="Btwlzx Dqqes Eqlpj2 Tjhvqujs lqoqjy bpg Eqfxtx Xcwwtt";//הצהרה על מחרוזת המכילה את הקוד המוצפן כמבוקש במטלה
	decode(string);
	printf("\nThe decrypted string is: ");
	puts(string);
	system("pause");
}

//פונקציה המקבלת מחרוזת עם תוכן מוצפן, הפונקציה תחסר את הערך האסקי על פי מיקום האות במילה, החל מ1 ותתקדם ב1 באות הבאה וכאשר יש רווח ומילה חדשה שוב תתחיל מ1, התוכן המפוענח מוחזר לפונקציה הראשית על ידי המצביע למחרוזת
void decode(char *str)
{
	int i = 0, j = 1;
	while ((str[i] != '\n') && (str[i] != '\0'))
	{
		if (str[i] != ' ')
		{
			str[i] = str[i] - j;
			i++;
			j++;
		}
		else if (str[i] == ' ')
		{
			j = 1;
			i++;
		}
	}
}

/*....ex5....*/
void Ex5()
{
	char declaration_str[100];
	char file_name[10] = "input.txt";//הצהרה על מחרוזת המכילה את שם הקובץ כמבוקש בנתוני השאלה
	printf("the file is %s ,  ", file_name);
	printf("Enter the declaration of variables:\n");
	rewind(stdin);
	gets(declaration_str);
	memoryReport(declaration_str, file_name);
	printtFileTxt(file_name);
	system("pause");
}

//פונקציה המקבלת שתי מחרוזות, אחת היא שם של קובץ והשניה היא משתנים, הפונקציה מחשבת את הזיכרון שיש להקצות למשתנים ותשמור את התוצאה בקובץ הטקסט
void memoryReport(char *declarition, char *file_name)
{
	char str[100], str_arr[100];
	int i = 0, j = 0, str_length, size_unit, size_pointer, q, ind, flag = 0, y = 0, k = 1, p, arr1 = 0;
	FILE *f = fopen(file_name, "w");
	if (f == NULL)
	{
		printf("the File %s could not be opened\n", f);
	}
	str_length = strlen(declarition);
	while (declarition[i] == ' ')
	{
		i++;
	}
	if (declarition[i] == 'i')
	{
		size_unit = sizeof(int);
		size_pointer = sizeof(int*);
	}
	else if (declarition[i] == 's')
	{
		size_unit = sizeof(short);
		size_pointer = sizeof(short*);
	}
	else if (declarition[i] == 'c')
	{
		size_unit = sizeof(char);
		size_pointer = sizeof(char*);
	}
	else if (declarition[i] == 'f')
	{
		size_unit = sizeof(float);
		size_pointer = sizeof(float*);
	}
	else if (declarition[i] == 'd')
	{
		size_unit = sizeof(double);
		size_pointer = sizeof(double*);
	}
	else if (declarition[i] == 'l')
	{
		while (declarition[i + 5] == ' ')
		{
			i++;
		}
		if ((declarition[i + 5] == 'l') && (declarition[i + 6] == 'o') && (declarition[i + 7] == 'n') && (declarition[i + 8] == 'g'))
		{
			size_unit = sizeof(long long);
			size_pointer = sizeof(long long*);
			while (declarition[i] != ' ')
			{
				i++;
			}
			while (declarition[i] == ' ')
			{
				i++;
			}
		}
		else
		{
			size_unit = sizeof(long);
			size_pointer = sizeof(long*);
		}
	}
	while (declarition[i] != ' ')//לרוץ עד סוף סוג ההצהרה
	{
		i++;
	}
	while (declarition[i] == ' ')//לרוץ עד המשתנה הראשון
	{
		i++;
	}
	while (declarition[i] != ';')
	{
		while ((declarition[i] != ';') && (declarition[i] != ','))
		{
			if (declarition[i] != ' ')
			{
				str[j] = declarition[i];
				i++;
				j++;
			}
			else
				i++;
		}
		str[j] = '\0';
		if (str[j - 1] == ']')
		{
			for (q = 0; q < j; q++)
			{
				if (str[q] == '[')
				{
					while (str[q] == ' ')
					{
						q++;
					}
					q++;
					ind = q;
					for (; ind < j; ind++)
					{
						if (str[ind] < '0'&&str[ind] < '9')
							flag = 1;
					}
					ind = 0;
					if (flag == 0)
					{
						for (; q < j - 1; q++)
						{
							str_arr[ind] = str[q];
							ind++;
						}
						str_arr[ind] = '\0';
						str_length = strlen(str_arr);
						arr1 = 1;
					}

				}
			}
		}
		if (arr1 == 1)
		{
			for (p = str_length - 1; p >= 0; p--)
			{
				y += (str_arr[p] - '0')*k;
				k = k * 10;
			}
			fprintf(f, " %s requires %d bytes\n", str, size_unit*y);
			k = 1;
			y = 0;
		}
		else if (str[0] == '*')
		{
			str_length = strlen(str);
			for (p = 0; p < str_length - 1; p++)
			{
				str[p] = str[p + 1];
			}
			str[p] = '\0';
			fprintf(f, " %s requires %d bytes\n", str, size_pointer);
		}
		else
			if (size_unit == 1)
				fprintf(f, " %s requires %d bytes\n", str, size_unit);
			else
				fprintf(f, " %s requires %d bytes\n", str, size_unit);
		arr1 = 0;
		j = 0;
		while ((declarition[i] == ' ') && (declarition[i] != ';'))
		{
			i++;
		}
		while ((declarition[i] == ',') && (declarition[i] != ';'))
		{
			i++;
		}
		while ((declarition[i] == ' ') && (declarition[i] != ';'))
		{
			i++;
		}
	}
	fclose(f);
}

//פונקציה המדפיסה את התוכן השמור בקובץ הטקסט
void printtFileTxt(char *name_of_file)
{
	FILE *file;
	char st[100];
	if ((file = fopen(name_of_file, "r")) == NULL)
		printf(" the File %s could not be opened\n",file);
	fgets(st, 100, file);
	while (!feof(file)) {
		printf("%s", st);
		fgets(st, 30, file);
	}
}