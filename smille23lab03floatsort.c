/* Sherilyn Miller
CS332
smille23
lab03 practice

Compile : 
gcc -Wall smille23lab03floatsort.c -o lab03fs

run:
./lab03fs


This file is a practice test for the integration of char sorting
*/

// Library declarations
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function prototype
void insertionSort(float *array, int length);
void displayArray(float *array, int size);

//Main function
int main(void)
{
    int n;
    printf("Please enter the number of elements in the array: ");
    scanf("%d", &n);

    // array declaration
float *array = malloc(n * sizeof(float));

// for each element in the array, iterate via loop to prompt the user for an input to store in the array
for(int i = 0; i< n; i++){
    printf("Please enter elements into the array: ");
    scanf("%f", &array[i]);
}
for (int i = 0; i < n  ; i++)
{
    printf("array[%d] = %f\n", i, array[i]);
}
    displayArray(array, n);
    insertionSort(array, n);
    displayArray(array, n);

    free(array);

return 0;
}

void displayArray(float *array, int size)
{
    printf("[");
    for (int i = 0; i < size -1; i++)
    {
        printf("%f, ", array[i]);
    }
    printf("%f]\n", array[size - 1]);
}

//Function definition
void insertionSort(float *array, int size){
    // for each element in the array, save the current element to key. save the previous element to j
    for (int i = 1; i < size; i++){
        float key = array[i];
        int j = i -1;
        // while j is greater than or equal to 0 and the element at j is greater than key, shift the element at j to the right
        while (j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j = j -1;

        }
        // insert key to its correct position
        array[j + 1] = key;
        }

    }
