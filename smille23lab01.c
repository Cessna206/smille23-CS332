/* Sherilyn Miller
CS332
smille23
lab01

Compile : 
gcc -Wall smille23lab01.c -o lab01

run:
./lab01

*/

// Library declarations
#include <stdbool.h>
#include <stdio.h>

//Function prototype
bool isPrime(int num);

//Program start, grabs space in memory
int main() {
    //variable declaration
    int number;
//prompt creation and user input
    printf("Enter a number: ");
    scanf("%d", &number);
//function call and output
    if (isPrime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }

    return 0;
}
//Function definition
bool isPrime(int num) {
    // variable declaration
    int count = 0;
// check if number is less than or equal to 1, if so return not prime
    if (num <= 1) {
        return false;
    }
// loop to count the number of divisors of num
    for (int i = 1; i <= num; i++) {
        // check if num is divisible by i, if so increment i
        if (num % i == 0) {
            //check if num is divisible by i, if so increment count
            count++;
        }
    }

    if (count == 2) {
        // if count is 2, then num is prime, return true
        return true;
    } else {
        // if count is not 2, then num is not prime, return false
        return false;
    }
}