/* Sherilyn Miller
CS332
smille23
lab02

Compile : 
gcc -Wall smille23lab02.c -o lab02

run:
./lab02

*/

// Library declarations
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function prototype
void insertionSort(int array[], int length);

//Main function
int main(void)
{
    int n;
    printf("Please enter the number of elements in the array: ");
    scanf("%d", &n);

    // array declaration
int array [100] ={0};

// for each element in the array, iterate via loop to prompt the user for an input to store in the array
for(int i = 0; i< n; i++){
    printf("Please enter elements into the array: ");
    scanf("%d", &array[i]);
}
// for each element in the array, iterate via loop to print the elements
for (int i = 0; i < n; i++){
    printf("%d\n", array[i]);

}
// call sorting algo
insertionSort(array, n);

// for each element in the array, iterate via loop to print the elements
for (int i = 0; i < n  ; i++){
    printf("array[%d] = %d\n", i, array[i]);

}
//end program
return 0;

}
//Function definition
void insertionSort(int array[], int length){
    // for each element in the array, save the current element to key. save the previous element to j
    for (int i = 1; i < length; i++){
        int key = array[i];
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


/* 

Below is lab practice and should be ignored. 

srand(time(NULL));
 

int array[100];
fillArray(array, 100, 200);

    for (int i = 0; i <100
    ; i++)
    printf("array[%d] = %d\n", i, array[i]);

    printf("min = %d\n", findMin(array, 100));

    return 0;

}
int findMin(int array[], int length){
    int min = array[0];
    for (int i = 1; i < length; i++){
        printf("Checking array[%d] = %d\n ", i, array[i]);;
        if (array[i] < min){
            min = array[i];
            printf("new min found:LL %d\n ", min);
        }
    }
    return min;
}

void fillArray(int array[], int length, int max){
    for (int i = 0; i < length; i++)
    array[i] = (rand() % max) +1;
    */



