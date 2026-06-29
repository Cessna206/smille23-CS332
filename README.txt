Smille23 CS332 Lab04

Outcome:
This program will take two files and append the contends of the second file to the first file. 
Its purpose is to explore the UNIX I/O functionality. 

Instructions:
You will need to make two files via 'touch <filename>.txt' (remove apostrophies and comparison symbols) and then 'code <filename.txt>' 
Here you will enter the contents of your file. Save the file and close them. 
Check they are properly saved by running cat <filename1>.txt
Repeat for file2. 

On the CLI, run gcc -Wall smille23lab04.c -o lab04
Then run ./lab04 <filename1>.txt <filename2>.txt

To inspect the results, run cat <filename1>.txt 
There you should see the contents of file2 copied to file1. 