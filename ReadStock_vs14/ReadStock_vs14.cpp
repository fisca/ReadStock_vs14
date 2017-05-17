// ReadStock_vs14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
	int lotNumber;
	char name[20];
	double price;
	int amount;
} Product;

void PrintStock(FILE*, char);
void SplitString(char *str_input, char dem, char *str_output[], int total_row, int max_lenght);
void ShowProduct(Product);

int main()
{
	FILE *fpin;
	char op, fileName[] = "c:\\data\\Stock.txt";

	if (fopen_s(&fpin, fileName, "r") != 0)
	{
		printf("Cannot open or read file %s\n", fileName);
		return 0;
	}

	printf("*** Stock Information ***\n");
	
	while (1)
	{
		fseek(stdin, 0, SEEK_END); // Clear Input Buffer

		printf("Product < (T)en | < (F)iffty | >= (O)ne hundred | e(X)it : ");		
		fflush(stdin); //scanf("%c", &option);
		op = toupper(getchar());

		switch (op)
		{
			case 'T': case 'F': case 'O':
				PrintStock(fpin, op); break;
			case 'X': 
				fclose(fpin); printf("\nThank you. Good Bye. Close in "); for (int i = 3; i > 0; i--) { printf("%d ", i); Sleep(1000); } return 0;
			default:
				printf("\nWrong input! Try Again.\n");
		}
		printf("\n");		
	}
	fclose(fpin);

	return 0;
}

void PrintStock(FILE *fpin, char op)
{
	printf("\nLot_Number Name               Price   Amount\n");
	printf("--------------------------------------------\n");
	char str[100];

	rewind(fpin);

	while (fgets(str, sizeof(str) - 1, fpin) != NULL)
	{
		Product prod;
		const int total_row = 4, max_length = 20;
		char *arr[total_row], dem = ',';
		
		for (int i = 0; i < total_row; i++)
		{
			arr[i] = (char*)malloc(max_length * sizeof(char)); //*** IMPORTANT ***
			char *p = arr[i];
			p[0] = '\0';
		}	

		SplitString(str, dem, arr, total_row, max_length);

		prod.lotNumber = atoi(arr[0]);
		strcpy_s(prod.name, sizeof(prod.name), arr[1]);
		prod.price = atof(arr[2]);
		prod.amount = atoi(arr[3]);

		for (int i = 0; i < total_row; i++)
			free(arr[i]);
		
		switch (op)
		{
			case 'T': if (prod.amount < 10) ShowProduct(prod); break;
			case 'F': if (prod.amount < 50) ShowProduct(prod); break;
			case 'O': if (prod.amount >= 100) ShowProduct(prod); break;
		}

	}
}

void SplitString(char *str, char dem, char *arr[], int total_row, int max_length)
{
	int j = 0, k = 0;
	for (int i = 0; i < (int)strlen(str); i++)
	{
		if (str[i] != dem)
		{
			char *p = (char*)malloc(2 * sizeof(char));
			p[0] = str[i];
			p[1] = '\0';

			strcat_s(arr[k], max_length, p);

			free(p);
		}
		else
		{
			strcat_s(arr[k], max_length, "\0"); //char *p = arr[k]; p[i] = '\0';
			k++;
		}
		j = k;
	}	
}

void ShowProduct(Product product)
{
	printf("%-10d %-18s %-6.2lf  %d\n", product.lotNumber, product.name, product.price, product.amount);
}

