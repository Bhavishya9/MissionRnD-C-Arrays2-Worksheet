/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

struct transaction {
	int amount;
	char date[11];
	char description[20];
};

void convert(char *charDate, int intDate[]);
int search(struct transaction *Arr, int[], int);
int equality(struct transaction *Arr, int);

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (Arr->date == '\0' || len <= 0 || date == '\0' || Arr->description == '\0' || Arr->amount<0 || Arr == '\0')// check for all the invalid input cases
		return '\0';
	
	int intDate[3] = { 0 };//declare the an integer array to convert char *date to integer array
	convert(date, intDate);//call the function which changes date from char to integer array
	int equal_check = equality(Arr, len);//check if all the inputs in the array are equal
	if (equal_check == 1)//check if all the inputs are equal in the array
		return 0; //then return 0 
	int return_value = search(Arr, intDate, len);//else call the search function 
	if (return_value == -1)//if the date is not present then return 0
		return 0;
	else //if it is present then return the number of greater dates
		return len - return_value-1;//total - index of the date found - 1
}

int equality(struct  transaction *Arr,int len)// function which checks for equality 
{
	int index = 0,flag=0;
	for (index = 0; index <= len - 2; index++)//run the loop for length-2 times
	{
		for (int index1 = 0; index1 < 10; index1++)//run the inner loop length of date in the structure times
		{
			if (Arr[index].date[index1] == Arr[index + 1].date[index1])//compare each index of the date in adjacent arrays
				continue;
			else
			{
				flag = 1;//if even once the above condition fails break from the loop
				break;
			}
		}
		if (flag == 1)//break from the outer loop if date in the adjacent arrays
			break;
	}
	if (index == len-1)//check the no of times the outer loop executed 
		return 1;//if index==length-1 times then all the elements in the loop are equal then return 1
	else//if not return 0
		return 0;
}

void convert(char *charDate, int intDate[])//function converts char array of date into integer array
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

int search(struct transaction *Arr, int intDate[],int len)//checks if the date is present in the structure
{
	/*implements binary search*/
	int low = 0;
	int high = len - 1;
	while (low < high)
	{
		int mid = (low + high) / 2;
		int transaction_date[3] = { 0 };
		convert((Arr+mid)->date, transaction_date);//converting char Date into int date
		for (int index = 2; index >= 0; index--)//compare the dates
		{
			if (transaction_date[index]>intDate[index])//check for years
			{
				high = mid - 1;
				break;
			}
			else if (transaction_date[index] < intDate[index])//checks for months
			{
				low = mid + 1;
				break;
			}
			else// if all the values of date array are equal then we found the required date
			{
				if (index == 0)//return the index of the date 
					return mid;
			}
		}
	}
	return -1;
}