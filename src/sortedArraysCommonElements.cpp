/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

void convert_Date(char *charDate, int intDate[])//function converts char array of date into integer array
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

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	if (A == '\0' || B == '\0' || ALen <= 0 || BLen <= 0)//checks for all the invalid input cases
		return NULL;
	int transactionDate1[3] = { 0 }, transactionDate2[3] = { 0 };//take two temporary arrays
	int flag1 = 0, flag2 = 0;
	int index = 0, index1 = 0, index2 = 0, length = 0;
	if (ALen <= BLen)//check which of the two given lengths is minimum
		length = ALen;
	else
		length = BLen;
	struct transaction *result = (struct transaction*)malloc(length*sizeof(transaction));//with the minimum length create the result struct array
	int count = 0;//keep a count of common elements
	while (index1 < ALen && index1 < BLen)//run the loop until one of the array ends
	{
		if (flag1 == 0)//if flag1=0 then convert the char date in A array into integer array
		{
			convert_Date((A + index1)->date, transactionDate1);
		}
		if (flag2 == 0)//if flag2=0 then convert the char date in B array into integer array
		{
			convert_Date((B + index2)->date, transactionDate2);
		}
		for (int i = 2; i >= 0; i--)//compare the dates in the two temporary integer arrays
		{
			if (transactionDate1[i] > transactionDate2[i])//if A is greater then copy B
			{
				index2++;// increment the index of B
				flag1 = 1;
				flag2 = 0;
				for (int j = 0; j < 3; j++)//make second temporary integer array to zero
					transactionDate2[j] = 0;
				break;
			}
			else if (transactionDate1[i] < transactionDate2[i])//if A is less then copy A
			{
				index1++;// increment the index of A
				for (int j = 0; j < 3; j++)// make first temporary integer array to zero
					transactionDate1[j] = 0;
				flag2 = 1;
				flag1 = 0;
				break;
			}
			else
			{
				if (i == 0)//if the dates are equal i.e. years and months and day are equal
				{
					result[index++] = A[index1++];//copy the value of A[index1] or B[index2] and increment the result, A to next index
					index2++;//increment the B to next index
					count++;//count the number of values which are equal
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
	if (count == 0)//if no values are equal then return zero
		return NULL;
	return result;//else return the result array
}