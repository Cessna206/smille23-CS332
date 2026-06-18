/* Sherilyn Miller
CS332
smille23
lab02

Compile : 
gcc -Wall smille23_hw01.c -o hw01

run:
./hw01

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int sumOfDigits(int n);
int UABMaxMinDiff(int arr[], int size); 
void replaceEvenWithZero(int arr[], int size);
int perfectSquare(int n);
int countVowels(char str[]);

int main(void){
 
 /* sumOfDigits */
    printf("sumOfDigits(123) = %d\n", sumOfDigits(123));
    printf("sumOfDigits(405) = %d\n", sumOfDigits(405));
    printf("sumOfDigits(0) = %d\n", sumOfDigits(0));
    printf("sumOfDigits(7) = %d\n", sumOfDigits(7));
    printf("sumOfDigits(-308) = %d\n\n", sumOfDigits(-308));

    /* UABMaxMinDiff */
    int arr1[] = {3, 7, 2, 9};
    int arr2[] = {5, 5, 5, 5, 5, 5};
    int arr3[] = {-2, 4, -1, 6, 5};

    printf("UABMaxMinDiff(arr1) = %d\n",
           UABMaxMinDiff(arr1, 4));

    printf("UABMaxMinDiff(arr2) = %d\n",
           UABMaxMinDiff(arr2, 6));

    printf("UABMaxMinDiff(arr3) = %d\n\n",
           UABMaxMinDiff(arr3, 5));

    /* replaceEvenWithZero */
    int arr4[] = {1, 2, 3, 4};
    int arr5[] = {2, 4, 6};
    int arr6[] = {1, 3, 5};

    replaceEvenWithZero(arr4, 4);
    replaceEvenWithZero(arr5, 3);
    replaceEvenWithZero(arr6, 3);

    printf("replaceEvenWithZero([1,2,3,4]) = ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", arr4[i]);
    }
    printf("\n");

    printf("replaceEvenWithZero([2,4,6]) = ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", arr5[i]);
    }
    printf("\n");

    printf("replaceEvenWithZero([1,3,5]) = ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", arr6[i]);
    }
    printf("\n\n");

    /* perfectSquare */
    printf("perfectSquare(16) = %s\n",
           perfectSquare(16) ? "True" : "False");

    printf("perfectSquare(15) = %s\n",
           perfectSquare(15) ? "True" : "False");

    printf("perfectSquare(25) = %s\n",
           perfectSquare(25) ? "True" : "False");

    printf("perfectSquare(36) = %s\n\n",
           perfectSquare(36) ? "True" : "False");

    /* countVowels */
    printf("countVowels(\"Hello World\") = %d\n",
           countVowels("Hello World"));

    printf("countVowels(\"UAB CS\") = %d\n",
           countVowels("UAB CS"));

    printf("countVowels(\"Python\") = %d\n",
           countVowels("Python"));

    printf("countVowels(\"aeiou\") = %d\n",
           countVowels("aeiou"));

    return 0;

/*

Below is the implementation for user input I utilized for testing the functions 
In order to more closely follow the assignment, I have removed them and implemented the required test cases above

 int n;

    printf("Please enter 2 or more digit number: ");
    scanf("%d", &n);
    printf("Sum of digits: %d\n", sumOfDigits(n));

    int size;
  
    printf("Please enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];
    // asks user for size
    for(int i = 0; i < size; i++){
    printf("Please enter elements into the array: ");
    scanf("%d", &arr[i]);
    // asks user for elements
     }
    printf("Difference between max and min: %d\n", UABMaxMinDiff(arr, size));

// calls function
    int arr1[5];
// initializes the array of size 5
    for(int i = 0; i < 5; i++){

    printf("Enter 5 ements into the array: ");
    scanf("%d", &arr1[i]);
  // for loop to iterate through the array 5 times and assigns user input to each element
}
    replaceEvenWithZero(arr1, 5);
// function call

    printf("Even numbers replaced with zero: \n");
// prints the array after replacing even numbers with zero
    for(int i = 0; i < 5; i++){
    printf("%d ", arr1[i]);
}
    printf("\n");



    printf("Enter a number to check if it is a perfect square: ");
    scanf("%d", &n);
    if (perfectSquare(n)){
        // calls the perfectSquare function
        printf("%d is a perfect square.\n", n);
    } else {
        printf("%d is not a perfect square.\n", n);
    }

    printf("Enter a string to count vowels: ");
    getchar(); // consume the newline character
    char str[100];
    // declare a character array to store the input string
    fgets(str, sizeof(str), stdin);
    // fgets instead of scanf to read the entire line
    printf("Number of vowels: %d\n", countVowels(str));
    // print the number of vowels in the string

    return 0;
    */

}

int sumOfDigits(int n){
    int sum = 0;
    // start sum at zero
    if (n<= 0){
        return -1;
    }
    while(n != 0){
        // while n is not zero
        sum += n % 10;
        // add the remainder of n divided by 10 to sum
        n /= 10;
        // divide n by 10 and update n
    }
    return sum;
    // return the sum of the digits
}

int UABMaxMinDiff(int arr[], int size){
    int min;
    int max;
    min = arr[0];
    max = arr[0];
    //variable declaration
    for (int i = 1; i < size; i++){
        // for loop to iterate through the array
        if (arr[i] < min){
            min = arr[i];
            // if the current element is less than min, update min
        }
        if (arr[i] > max){
            max = arr[i];
            // if the current element is greater than max, update max

        }
    }
    return max - min; 
    // return the difference between max and min
}

void replaceEvenWithZero(int arr1[], int size){
    // function to replace even numbers with zero
    for (int i = 0; i < size; i++){
        // loop to iterate through the array
        if (arr1[i] % 2 == 0){
            // if the modulus of the current element is zero, it is even
            arr1[i] = 0;
            // set current element to zero
        }
    }
}

int perfectSquare(int n){
    // babylonian method for finding square root
    int s= 2;
    // s is the initial guess for the square root
    int s1;
    if (n < 0){
        return 0;
        // return 0 if n is negative
    }
    if (n == 0 || n == 1){
        return 1;
        // 0 or 1 handling
    }
    for(int i = 0; i < 10; i++){
        // iterate 10 times to find the square root
        s1 = (s + n/s)/2;
        // 2 + the number divided by the guess, divided by 2
        if (s == s1){
           break;
           // if the guess is the same as the previous guess, break
        }
           s = s1;
           // else update the guess
        }
        return s * s == n;
        // return true if the square of the guess equals the number, false otherwise
    }

int countVowels(char str[]){
    int count = 0;
    // count the number of vowels in the string
    for (int i = 0; str[i] != '\0'; i++) 
    // iterate through each character in the string
    {
       switch (toupper(str[i])) {
            // convert all characters to uppercase
           case 'A':
           case 'E':
           case 'I':
           case 'O':
           case 'U':
               count++;
               break;
           // check if the character is a vowel, increment the count
       }
    }
    return count;
    // return the count of vowels
}






