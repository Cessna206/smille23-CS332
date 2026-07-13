Sherilyn Miller
Smille23
CS332
Lab06

Desc:
This program reads in listings.csv, stores each row in a struct listing,
and sorts the data two different ways for the homework: alphabetically
by host_name, and numerically by price. Each sorted version is written
out to its own new csv file (sorted_by_host_name.csv and
sorted_by_price.csv).

Compile:
First, change directories via 'cd Lab06'
then run 'gcc -Wall -o lab06 smille23lab06.c'

run:
to run the code, type './lab06 listings.csv'
if no filename is given, it defaults to listings.csv in the current

make file:
I realize this is outside of the scope of the lab
however, if you would like to use its functionality
type 'make' and then you will have access to:
make run            --> Compiles and runs on listings.csv in one command
make clean          --> deletes the generated csv files 
make see
note: output files contain many rows. do not use cat to display them. rather, use
head -n 10 'filename.filetype'


