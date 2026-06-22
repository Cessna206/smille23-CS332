/* Sherilyn Miller
CS332
smille23
lab03 

Compile : 
gcc -Wall smille23lab03.c -o lab03

run:
./lab03


This file is a practice test for the integration of char sorting
*/

// Library declarations
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Function prototype
void insertionSort(char **array, int size);
void displayArray(char **array, int size);
void readArray(char **array, int size);

//Main function
int main(void)
{
    int n;
    printf("Please enter the number of elements in the array: ");
    scanf("%d", &n);
    // error handlinh
    if (n <= 0)
    {
        printf("Error: Invalid input.\n");
        return 1;
    }

    // array declaration and memory allocation
char **array = malloc(n * sizeof(char *));
// temp storage for user input

// calling the display and sort functions
    
    readArray(array, n);
    displayArray(array, n);
    insertionSort(array, n);
    displayArray(array, n);

    // free the allocated memory
    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
// end program
return 0;

}

// function definition
void readArray(char **array, int length)
{
    
char temp[100];

// for each element in the array, iterate via loop to prompt the user for an input to store in the array
for(int i = 0; i< length; i++){
    printf("Please enter elements into the array: ");
    scanf("%s", temp);
// calculate the size of the input string
    int length = strlen(temp);
    // allocate memory for the string
    array[i] = malloc((length + 1) * sizeof(char));
    // copy to temp
    strcpy(array[i], temp);

}
}

// function definition
void displayArray(char **array, int size)
{
   // print clenliness
    printf("[");
    // iterate through the array and print each element
    for (int i = 0; i < size -1; i++)
    {
        printf("%s, ", array[i]);
    }
    printf("%s]\n", array[size - 1]);
}

//Function definition
void insertionSort(char **array, int size){
    // for each element in the array, save the current element to key. save the previous element to j
    for (int i = 1; i < size; i++){
        char *key = array[i];
        // set j to the current element - 1
        int j = i -1;
        // while j is greater than or equal to zero, compare the element at j with key
        while (j >= 0 && strcmp(array[j], key) > 0){
            // shift the element at j to the right
            array[j + 1] = array[j];
            // decrement j
            j = j -1;

        }
        // insert key to its correct position
        array[j + 1] = key;
        }

    }
