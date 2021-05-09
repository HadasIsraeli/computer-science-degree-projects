#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char* verylong ; //סעיף א

verylong input_long(void);
verylong add_verylong(verylong , verylong );
verylong multiply_verylong(verylong , verylong );
verylong reverse(verylong );
verylong add_zeros(verylong, int);
verylong remove_zeros(verylong);




//תבנית של העבודה
void main(void)
{

	verylong a, b, c;
	do {
		printf("enter the first long integer: ");
		a = input_long();
	} while (!a);
	do {
		printf("enter the second long integer: ");
		b = input_long();
	} while (!b);
	c = add_verylong(a, b);
	printf("%s + %s = %s\n", a, b, c);
	free(c);
	c = multiply_verylong(a, b);
	printf("%s * %s = %s\n", a, b, c);
	free(c);
	free(a);
	free(b);
	
}





verylong input_long(void)//סעיף ב
{
	char str[100];//מספר ארוך מאוד שניקלט
	verylong str2;//מחרוזת דינאמית המספר הנקלט נכנס אליה 
	gets(str);//קליטת מחרוזת
	puts(str);//הדפסת מחרוזת
	str2 = (verylong)malloc(strlen(str) + 1);//(str)מחשב גודל של 2 
	strcpy(str2, str);//copy str to str2
	for (int i = 0; i < strlen(str2); i++)//בדיקת תקינות קלט- בדיקה האם במחרוזת הניקלטת יש מספרים בלבד
	{
		if (str2[i]<'0' || str[i]>'9')
		{
			printf("\n Invalid input, input must contian only digits\n");
			return NULL;
		}
	}
	return str2;
}

verylong add_verylong(verylong vl1, verylong vl2)//פונקציה המחברת את 2 המחרוזות שניקלטו
{
	int size_vl1 = strlen(vl1);//חישוב גודל מחרוזת ראשונה
	int size_vl2 = strlen(vl2);//חישוב גודל מחרוזת שניה
	int carry = 0, result = 0;
	int max_size = 0, i = 0;
	
	if (size_vl1 > size_vl2)//בדיקה מי המחרוזת הגדולה יותר
	{
		max_size = size_vl1;
	}
	else
	{
		max_size = size_vl2;
	}

	verylong total_result = (verylong)malloc(max_size + 2);//הגדרת משתנה של התוצאה הכללית בגודל של המחרוזת הגדולה ועוד 2 תאים 
	
	vl1 = reverse(vl1);//היפוך המחרוזת הראשונה
	vl2 = reverse(vl2);//היפוך המחרוזת השניה
	for (i = 0; i < max_size; i++)//חיבור המחרוזות
	{
		if (size_vl1 >= (i+1) && size_vl2 >= (i+1))
		{
			result = (vl1[i] - '0') + (vl2[i] - '0') + carry;
			carry = result / 10;
		}
		else
		{
			if ((i + 1) > size_vl1)
			{
				result = (vl2[i] - '0') + carry;
				carry = 0;
			}
			else 
			{
				result = (vl1[i] - '0') + carry;
				carry = 0;
			}
		}
		total_result[i] = (result % 10) + '0';
	}

	if (carry != 0)//הוספת נשא במידה והוא שווה לאחד
	{
		total_result[max_size] = '1';
	}
	else// \0- אחרת מוסיפים
	{
		total_result[max_size] = '\0';
	}
	return reverse(total_result);		
}



verylong reverse(verylong vl)//פונקציה המקבלת מחרוזת ומחזירה את המחרוזת ההפוכה
{
	int length = strlen(vl);
	verylong res = (verylong)malloc(length + 1);
	int count = 0;
	for (int i = strlen(vl) - 1; i >= 0; i--)
	{
		res[count] = vl[i];
		count++;
	}
	res[length] = '\0';
	return res;
}

   

verylong multiply_verylong(verylong vl1, verylong vl2)//פונקציה המקבלת שתי מחרוזות ומחזירה את הכפל בניהן
{
	int size_vl1 = strlen(vl1);//חישוב גודל מחרוזת ראשונה
	int size_vl2 = strlen(vl2);//חישוב גודל מחרוזת שניה
	int value = 0, carry = 0, i = 0, j = 0;
	verylong small_str = (verylong)malloc(100);
	verylong big_str = (verylong)malloc(100);

	if (size_vl1 > size_vl2)//בדיקה האם המחרוזת הראשונה היא הגדולה מבין השתיים
	{
		strcpy(small_str, vl2);//small_str העתקת המחרוזת הקטנה למחרוזת אחרת בשם 
		strcpy(big_str, vl1);//big_str העתקת המחרוזת הגדולה למחרוזת אחרת בשם 
	}
	else//בדיקה האם המחרוזת השניה היא הגדולה מבין השתיים
	{
		strcpy(small_str, vl1);//small_str העתקת המחרוזת הקטנה למחרוזת אחרת בשם
		strcpy(big_str, vl2);//big_str העתקת המחרוזת הגדולה למחרוזת אחרת בשם
	}
	

	verylong result = (verylong)malloc((strlen(big_str) * 2) + 1);
	result[strlen(big_str) * 2] = '\0';
	
	verylong total_result = (verylong)malloc((strlen(big_str) * 2) + 1);
	total_result[strlen(big_str) * 2] = '\0';
	
	

	for (i = 0; i < strlen(total_result); i++) //אתחול המחרוזת עם ערכי 0
	{
		total_result[i] = '0';
	}

	small_str = reverse(small_str);
	big_str = reverse(big_str);
	

	for (i = 0; i < strlen(big_str); i++)
	{
		for (j = 0; j < strlen(small_str); j++)
		{
			value = (big_str[i] - '0')*(small_str[j] - '0') + carry;
			carry = value / 10;
			result[j] = (value % 10) + '0';
			
			if (j == strlen(small_str) - 1) {
				
				result[strlen(small_str)] = carry + '0';
				result[strlen(small_str)+1] ='\0';

			}
			
		}
		carry = 0;
		result = reverse(result);
		result = add_zeros(result, i);
		total_result = add_verylong(total_result,result);
	}
	total_result = remove_zeros(total_result);
	return total_result;
}


verylong add_zeros(verylong vl, int amount)//הוספת אפסים לסוף המערך של המחרוזת
{
	int i = 0;
	char zero = '0';
	for (i = 0; i < amount; i++)
	{
		vl = strncat(vl, &zero, 1);
	}
	return vl;
}



verylong remove_zeros(verylong vl)//הורדת אפסים מיותרים 
{
	vl = reverse(vl);
	int length = strlen(vl);
	while (vl[length - 1] == '0')
	{
		vl[length - 1] = '\0';
		length = strlen(vl);
	}
	return reverse(vl);
}

