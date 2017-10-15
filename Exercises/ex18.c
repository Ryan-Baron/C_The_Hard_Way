#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
* Function name: die
* Arguments: input error message
* Return: exits code if called
* Info: This relays the error messages if our code breaks
*/
void die(const char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	
	exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);

/**
* Function name: bubble_sort
* Arguments: A pointer to the array of numbers, the count, 
* Return: a pointer to a sorted array
* Info: Uses compare_cb to do a bubblesort of the numbers
*/
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));
	
	if (!target)
		die("Memory error.");
	
	memcpy(target, numbers, count * sizeof(int));
	
	for (i = 0; i < count; i++) {
		for (j = 0; j < count -1; j++) {
			if (cmp(target[j], target[j + 1]) > 0) {
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}
	return target;
}

/**
* Function name: sorted_order(int a, int b)
* Arguments: two integers
* Return: returns integer 1 minus integer 2
* Info: sorts the order
*/
int sorted_order(int a, int b)
{
	return a - b;
}

/**
* Function name: reverse_order(int a, int b)
* Arguments: two integers
* Return: returns integer 2 minus integer 1
* Info: reversing the order
*/
int reverse_order(int a, int b)
{
	return b - a;
}

/**
* Function name: strange_order(int a, int b)
* Arguments: two integers
* Return: returns integer 2 minus integer 1
* Info: reversing the order
*/
int strange_order(int a, int b)
{
	if (a==0 ||b ==0) {
		return 0;
	} else {
		return a %b;
	}
}


/**
* Function name: test_sorting(int *numbers, int count, compare_cb cmp)
* Arguments: pointer to an array of numbers, the count function pointer
* Return: void
* Info: Checks to see if we have correctly sorted the array
*/
void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);
	
	if (!sorted)
		die("Failed to sort as requested.");
		
	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");
	
	free(sorted);
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 4 3 1 5 6");
	
	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;
	
	int *numbers = malloc(count * sizeof(int));
	if (!numbers) die("Memory error.");
	
	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}
	
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	
	free(numbers);
	
	return 0;
}






			

