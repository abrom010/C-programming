#include <stdio.h>

unsigned long int next = 1;

int rand(void)
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed)
{
	next = seed;
}

void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for(gap = n/2; gap > 0; gap /= 2)
		for(i = gap; i<n; i++)
			for(j=i-gap; j>=0 && v[j]<v[j+gap]; j-=gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

int main()
{
	srand(12345);
	int arr[10];

	for(int i=0; i<10; ++i) {
		arr[i] = rand();
	}
	
	shellsort(arr, 10);
	
	for(int i=0; i<10; ++i) {
		printf("%d, ", arr[i]);
	}
	
	return 0;
}
