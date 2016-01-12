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
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0)//checks the invalid input conditions
		return NULL;
	int transactionDate1[3] = { 0 }, transactionDate2[3] = { 0 };//take two temporary integer arrays
	int flag1 = 0, flag2 = 0, index = 0, index1 = 0, index2 = 0;
	struct transaction *result = (struct transaction*)malloc((ALen+BLen) * sizeof(struct transaction));//dynamically create the result stuct array
	while (index1<ALen && index2<BLen)//repeat the loop until one of the struct array ends
	{
		if (flag1 == 0)// if flag1 is zero then convert date in A array into integer array
		{
			converter((A + index1)->date, transactionDate1);
		}
		if (flag2 == 0)// if flag2 is zero then convert date in B array into integer array
		{
			converter((B + index2)->date, transactionDate2);
		}
		for (int i = 2; i >= 0; i--)//compare the dates in the two temporary integer arrays
		{
			if (transactionDate1[i] > transactionDate2[i])//if A is greater then copy B
			{
				result[index++] = B[index2++];// increment the index of B
				flag1 = 1;
				flag2 = 0;
				for (int j = 0; j < 3; j++)//make second temporary integer array to zero
					transactionDate2[j] = 0;
				break;
			}
			else if (transactionDate1[i] < transactionDate2[i])//if A is less then copy A
			{
				result[index++] = A[index1++];// increment the index of A
				flag2 = 1;
				flag1 = 0;
				for (int j = 0; j < 3; j++)// make first temporary integer array to zero
					transactionDate1[j] = 0;
				break;
			}
			else
			{
				if (i == 0)//if the dates are equal i.e. years and months and day are equal
				{
					result[index++] = A[index1++];//copy the value of A[index1] and increment the result, A to next index
					result[index++] = B[index2++];//copy the value of B[index2] and increment the result, B to next index
					flag1 = 0;
					flag2 = 0;
					for (int j = 0; j < 3; j++)// make both the temporary integer arrays to zero
					{
						transactionDate1[j] = 0;
						transactionDate2[j] = 0;
					}
				}
			}
		}
	}
	while (index1 < ALen && index < (ALen + BLen))//if A array is not copied completely then copy it to result
		result[index++] = A[index1++];
	while (index2 < BLen && index < (ALen + BLen))//if B array is not copied completely then copy it to result
		result[index++] = B[index2++];
	return result;
}