#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char* verylong ; //���� �

verylong input_long(void);
verylong add_verylong(verylong , verylong );
verylong multiply_verylong(verylong , verylong );
verylong reverse(verylong );
verylong add_zeros(verylong, int);
verylong remove_zeros(verylong);




//����� �� ������
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





verylong input_long(void)//���� �
{
	char str[100];//���� ���� ���� ������
	verylong str2;//������ ������� ����� ����� ���� ���� 
	gets(str);//����� ������
	puts(str);//����� ������
	str2 = (verylong)malloc(strlen(str) + 1);//(str)���� ���� �� 2 
	strcpy(str2, str);//copy str to str2
	for (int i = 0; i < strlen(str2); i++)//����� ������ ���- ����� ��� ������� ������� �� ������ ����
	{
		if (str2[i]<'0' || str[i]>'9')
		{
			printf("\n Invalid input, input must contian only digits\n");
			return NULL;
		}
	}
	return str2;
}

verylong add_verylong(verylong vl1, verylong vl2)//������� ������ �� 2 �������� �������
{
	int size_vl1 = strlen(vl1);//����� ���� ������ ������
	int size_vl2 = strlen(vl2);//����� ���� ������ ����
	int carry = 0, result = 0;
	int max_size = 0, i = 0;
	
	if (size_vl1 > size_vl2)//����� �� ������� ������ ����
	{
		max_size = size_vl1;
	}
	else
	{
		max_size = size_vl2;
	}

	verylong total_result = (verylong)malloc(max_size + 2);//����� ����� �� ������ ������ ����� �� ������� ������ ���� 2 ���� 
	
	vl1 = reverse(vl1);//����� ������� �������
	vl2 = reverse(vl2);//����� ������� �����
	for (i = 0; i < max_size; i++)//����� ��������
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

	if (carry != 0)//����� ��� ����� ���� ���� ����
	{
		total_result[max_size] = '1';
	}
	else// \0- ���� �������
	{
		total_result[max_size] = '\0';
	}
	return reverse(total_result);		
}



verylong reverse(verylong vl)//������� ������ ������ ������� �� ������� ������
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

   

verylong multiply_verylong(verylong vl1, verylong vl2)//������� ������ ��� ������� ������� �� ���� �����
{
	int size_vl1 = strlen(vl1);//����� ���� ������ ������
	int size_vl2 = strlen(vl2);//����� ���� ������ ����
	int value = 0, carry = 0, i = 0, j = 0;
	verylong small_str = (verylong)malloc(100);
	verylong big_str = (verylong)malloc(100);

	if (size_vl1 > size_vl2)//����� ��� ������� ������� ��� ������ ���� ������
	{
		strcpy(small_str, vl2);//small_str ����� ������� ����� ������� ���� ��� 
		strcpy(big_str, vl1);//big_str ����� ������� ������ ������� ���� ��� 
	}
	else//����� ��� ������� ����� ��� ������ ���� ������
	{
		strcpy(small_str, vl1);//small_str ����� ������� ����� ������� ���� ���
		strcpy(big_str, vl2);//big_str ����� ������� ������ ������� ���� ���
	}
	

	verylong result = (verylong)malloc((strlen(big_str) * 2) + 1);
	result[strlen(big_str) * 2] = '\0';
	
	verylong total_result = (verylong)malloc((strlen(big_str) * 2) + 1);
	total_result[strlen(big_str) * 2] = '\0';
	
	

	for (i = 0; i < strlen(total_result); i++) //����� ������� �� ���� 0
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


verylong add_zeros(verylong vl, int amount)//����� ����� ���� ����� �� �������
{
	int i = 0;
	char zero = '0';
	for (i = 0; i < amount; i++)
	{
		vl = strncat(vl, &zero, 1);
	}
	return vl;
}



verylong remove_zeros(verylong vl)//����� ����� ������� 
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

