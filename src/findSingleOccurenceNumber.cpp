/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/
void quicksort(int[], int, int);

int findSingleOccurenceNumber(int *A, int len) {
	if (len >= 1 && A != '\0')
	{
		quicksort(A, 0, len - 1);
		int count = 0;
		for (int index = 1; index < len - 1; index++)
		{
			if (A[index - 1] != A[index] && A[index] != A[index + 1])
				return A[index];
		}
		if (A[0] != A[1])
			return A[0];
		if (A[len - 2] != A[len - 1])
			return A[len - 1];
		return -1;
	}
	return -1;
}

void quicksort(int A[], int low, int high)
{
	int pivot, j, temp, i;

	if (low < high){
		pivot = low;
		i = low;
		j = high;

		while (i < j){
			while (A[i] <= A[pivot] && i < high)
				i++;
			while (A[j] > A[pivot])
				j--;
			if (i < j){
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}

		temp = A[pivot];
		A[pivot] = A[j];
		A[j] = temp;
		quicksort(A, low, j - 1);
		quicksort(A, j + 1, high);

	}
}