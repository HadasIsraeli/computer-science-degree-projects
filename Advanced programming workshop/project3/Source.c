
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 8

typedef struct Employee // ex 1 struct
{
	int code;
	char name[15];
	float salary;
}employee;

typedef char board[SIZE][SIZE]; // ex 3 matrix typedef
board bin_board;

void Ex1_main();
void Ex2_main();
void Ex3_main();

void create_bin_file(char* filename);//ex 1 functions
void updateSalary(char* filename, float threshold);
void print_file(char* filename);

char* codingToShortString(char* dig_str); // ex 2 functions
void printEncodedString(char* short_dig_str, char* dig_str);

void fillBoard(); // ex 3 functions
unsigned long long boardToBits();
void displayBinaryBoard(unsigned long long crypted_num);
void display(unsigned long long crypted_num);

int main() // ex 4 (menu)
{
	int option = 0;
	while (1)
	{
		void(*p[3])() = { Ex1_main, Ex2_main, Ex3_main };
		printf("\nSelect the exercise (1-3) or enter 0 to exit: ");
		scanf("%d", &option);
		if (option == 0)
		{
			break;
		}
		switch (option)
		{
		case 1:
			(*p[0])();
			break;
		case 2:
			(*p[1])();
			break;
		case 3:
			(*p[2])();
			break;
		default:
			printf("\nInvalid choice! Choose the exercise (1-3) again.\n");
			break;
		}
	}
	return 0;
}

void Ex1_main()
{
	int option = 0;
	float threshold;
	while (option != 4)
	{
		printf("Ex 1:\nChoose your option:\n1) Create the file\n2) Update the salary\n3) Print file\n4) Exit... (continue to the next exercise)\n");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			create_bin_file("input.txt");
			break;
		case 2:
			printf("Set the salary threshold: ");
			scanf("%f", &threshold);
			updateSalary("input.txt", threshold);
			break;
		case 3:
			print_file("input.txt");
			print_file("temp.txt");
			break;
		default:
			break;
		}
	}
}

void create_bin_file(char* filename)
{
	employee var;
	char ch;
	FILE *fp;
	fp = fopen(filename, "wb");
	if (!fp)
	{
		return;
	}
	while (1)
	{
		printf("Enter the code: ");
		scanf("%d", &var.code);
		printf("Enter the name (max 15): ");
		scanf("%15s", var.name);
		printf("Enter the salary: ");
		scanf("%f", &var.salary);
		fwrite(&var, sizeof(employee), 1, fp);
		getchar();
		printf("Continue the input into the file? Press EOF to stop, else - press any key to continue the input: ");
		ch = getchar();
		if (ch == EOF)
		{
			break;
		}
	}
	fclose(fp);
}

void updateSalary(char* filename, float threshold)
{
	FILE *fp, *new_fp;
	int bonus, status;
	employee var;
	fp = fopen(filename, "rb");
	if (!fp)
	{
		return;
	}
	new_fp = fopen("temp.txt", "wb");
	if (!new_fp)
	{
		return;
	}
	while (fread(&var, sizeof(employee), 1, fp) > 0)
	{
		printf("Put the bonus to %s: ", var.name);
		scanf("%d", &bonus);
		if (var.salary + (float)bonus <= threshold)
		{
			var.salary = var.salary + (float)bonus;
			fwrite(&var, sizeof(employee), 1, new_fp);
		}
	}
	fclose(fp);
	status = remove(filename);
	fclose(new_fp);
}

void print_file(char* filename)
{
	FILE* fp;
	employee var;
	fp = fopen(filename, "rb");
	if (!fp)
	{
		return;
	}
	while (fread(&var, sizeof(employee), 1, fp) > 0)
	{
		printf("%d\t%s\t\t%.2f", var.code, var.name, var.salary);
		printf("\n");
	}
	fclose(fp);
}

void Ex2_main()
{
	char *dig_str, *short_dig_str;
	int len;
	printf("Enter the length of the number: ");
	scanf("%d", &len);
	dig_str = (char*)calloc(len + 1, sizeof(char));
	getchar();
	printf("Enter the number: ");
	scanf("%s", dig_str);
	short_dig_str = codingToShortString(dig_str);
	printEncodedString(short_dig_str, dig_str);
	free(dig_str);
	free(short_dig_str);
}

char* codingToShortString(char* dig_str)
{
	int i = 0, j = 0, new_size;
	char *short_dig_str;
	int n = strlen(dig_str);
	if (n % 2 == 0)
	{
		short_dig_str = (char*)calloc((n / 2) + 1, sizeof(char));
		new_size = (n / 2) + 1;
		while (dig_str[i])
		{
			short_dig_str[j] = dig_str[i] - '0';
			i++;
			short_dig_str[j] = short_dig_str[j] << 4;
			short_dig_str[j] = short_dig_str[j] | (dig_str[i] - '0');
			i++;
			j++;
		}
	}
	else
	{
		short_dig_str = (char*)calloc((n / 2) + 2, sizeof(char));
		new_size = (n / 2) + 2;
		short_dig_str[j] <<= 4;
		short_dig_str[j] = short_dig_str[j] | dig_str[i];
		i++;
		j++;
		while (dig_str[i])
		{
			short_dig_str[j] = dig_str[i] - '0';
			i++;
			short_dig_str[j] = short_dig_str[j] << 4;
			short_dig_str[j] = short_dig_str[j] | (dig_str[i] - '0');
			i++;
			j++;
		}
	}
	short_dig_str[new_size - 1] = '\0';
	return short_dig_str;
}

void printEncodedString(char* short_dig_str, char* dig_str)
{
	int i = 0, check = strlen(short_dig_str), n = strlen(dig_str);
	unsigned int c;
	unsigned char mask = 1 << 7, submask = 1 << 3;
	printf("%s = ", dig_str);
	if (n % 2 != 0)
	{
		for (c = 1; c <= 4; c++)
		{
			putchar(submask & short_dig_str[i] ? '1' : '0');
			short_dig_str[i] <<= 1;
		}
		putchar(' ');
		i++;
		for (; i < check; i++)
		{
			for (c = 1; c <= 8; c++)
			{
				putchar(mask & short_dig_str[i] ? '1' : '0');
				short_dig_str[i] <<= 1;
				if (c % 4 == 0)
				{
					putchar(' ');
				}
			}
		}
	}
	else
	{
		for (; i < check; i++)
		{
			for (c = 1; c <= 8; c++)
			{
				putchar(mask & short_dig_str[i] ? '1' : '0');
				short_dig_str[i] <<= 1;
				if (c % 4 == 0)
				{
					putchar(' ');
				}
			}
		}
	}
}

void Ex3_main()
{
	unsigned long long crypted_num;
	fillBoard();
	crypted_num = boardToBits();
	display(crypted_num);
}

void fillBoard()
{
	char bin_value;
	int i, j;
	time_t t;
	srand((unsigned)time(&t));
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			bin_value = '0' + rand() % 2;
			bin_board[i][j] = bin_value;
		}
	}
	printf("The randomized binary matrix is:\n");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("%c\t", bin_board[i][j]);
		}
		printf("\n");
	}
}

unsigned long long boardToBits()
{
	unsigned long long crypted_num = 0;
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			crypted_num = (crypted_num << 1) | (unsigned long long)((bin_board[i][j]) - '0');
		}
	}
	return crypted_num;
}

void display(unsigned long long crypted_num)
{
	char new_board[SIZE][SIZE];
	int i, j;
	for (i = SIZE - 1; i >= 0; i--)
	{
		for (j = SIZE - 1; j >= 0; j--)
		{
			new_board[i][j] = (crypted_num % 2) + '0';
			crypted_num /= 2;
		}
	}
	printf("\nThe restored matrix is:\n");
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("%c\t", new_board[i][j]);
		}
		printf("\n");
	}
}