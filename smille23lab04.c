/* Sherilyn Miller
CS332
smille23
lab04 

Compile : 
gcc -Wall smille23lab04.c -o lab04

run:
./lab04


This file is a practice test for the integration of char sorting
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int argc, char *argv[]) {
    int fd1, fd2;
    char buf[BUFFSIZE];
    ssize_t n;

    /* Check correct number of arguments */
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        exit(-1);
    }

    /* Check that the two filenames are not the same */
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Error: file1 and file2 must be different files.\n");
        exit(-1);
    }

    /* Open file2 (the source to be appended) in read-only mode */
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        printf("Error: could not open %s\n", argv[2]);
        exit(-1);
    }

    /* Open file1 for writing, appending to the end of its existing content.
     * We do NOT use O_TRUNC here, since we want to keep file1's original
     * content and add to it rather than overwrite it.
     */
    fd1 = open(argv[1], O_WRONLY | O_APPEND);
    if (fd1 < 0) {
        printf("Error: could not open %s\n", argv[1]);
        close(fd2);
        exit(-1);
    }

    /* Read from file2 in chunks and write each chunk to the end of file1 */
    while ((n = read(fd2, buf, BUFFSIZE)) > 0) {
        if (write(fd1, buf, n) != n) {
            printf("Error: write error while appending to %s\n", argv[1]);
            close(fd1);
            close(fd2);
            exit(-1);
        }
    }

    if (n < 0) {
        printf("Error: read error while reading %s\n", argv[2]);
        close(fd1);
        close(fd2);
        exit(-1);
    }

    /* Close both file descriptors */
    close(fd1);
    close(fd2);

    return 0;
}
