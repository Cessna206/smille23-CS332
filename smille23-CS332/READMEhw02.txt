CS332
smille23
Sherilyn Miller

Desc:
This program recursively iterates through your directory 
and filters by certain parameters. 

compile: type 'make' in the console

Run:
./hw02                                     Current directory
./hw02 <directory>                         Specific directory
./hw02 -S <directory>                      Lists all files with metadata. Directories show 0.
./hw02 -s <bytes> <directory>              List files with size less than or equal to <bytes>
./hw02 -f <name> <depth> <directory>       List files of a certain name and depth

Options can be combined 
./hw02 -S -s 1024 testdir
./hw02 -f jpg 2 -s 1024 testdir
./hw02 -S -f jpg 1 -s 1024 testdir
