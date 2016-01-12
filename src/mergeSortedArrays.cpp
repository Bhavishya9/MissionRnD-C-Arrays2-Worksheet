/*
OVERVIEW: You are given 2 bank statements that are ordered by date - Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

void converter(char *charDate, int intDate[])//function converts char array of date into integer array
{
	int j = 0;
	for (int i = 0; charDate[i] != '\0'; i++)
	{
		if (charDate[i] == '-')
		{
			j++;
			continue;
		}
		else
		{
			intDate[j] = intDate[j] * 10 + (charDate[i] - '0');
		}
	}
}


struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0)
		return NULL;
	int transactionDate1[3] = { 0 }, transactionDate2[3] = { 0 };
	int flag1 = 0, flag2 = 0, index = 0, index1 = 0, index2 = 0;
	struct transaction *result = (struct transaction*)malloc(6 * sizeof(struct transaction));
	while (index1<ALen && index2<BLen)
	{
		if (flag1 == 0)
		{
			converter((A + index1)->date, transactionDate1);
		}
		if (flag2 == 0)
		{
			converter((B + index2)->date, transactionDate2);
		}
		for (int i = 2; i >= 0; i--)
		{
			if (transactionDate1[i] > transactionDate2[i])
			{
				result[index++] = B[index2];
				index2++;
				flag1 = 1;
				flag2 = 0;
				for (int j = 0; j < 3; j++)
					transactionDate2[j] = 0;
				break;
			}
			else if (transactionDate1[i] < transactionDate2[i])
			{
				result[index++] = A[index1];
				index1++;
				for (int j = 0; j < 3; j++)
					transactionDate1[j] = 0;
				flag2 = 1;
				flag1 = 0;
				break;
			}
			else
			{
				if (i == 0)
				{
					result[index++] = A[index1];
					result[index++] = B[index2];
					index1++;
					index2++;
					flag1 = 0;
					flag2 = 0;
					for (int j = 0; j < 3; j++)
					{
						transactionDate1[j] = 0;
						transactionDate2[j] = 0;
					}
				}
			}
		}
	}
	while (index1 < ALen && index < (ALen + BLen))
	{
		result[index++] = A[index1++];
	}
	while (index2 < BLen && index < (ALen + BLen))
	{
		result[index++] = B[index2++];
	}
	for (int index = 0; index < (ALen + BLen); index++)
	{
		printf("%d", result[index].amount);
	}
	return result;
}