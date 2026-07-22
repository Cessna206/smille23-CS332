
/* Sherilyn Miller
CS332
smille23
lab07
 
Compile :
gcc -Wall smille23lab07.c -o lab07
 
run:
./lab07 <input_file>
 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
 
#define MAX_LINE 1024
#define MAX_ARGS 64
 
// splits a line like uname -a into an array
int parse_line(char *line, char *args[]) {
    int count = 0;
    char *token = strtok(line, " \t\n");
 
    //while loop for parsing the line into an array of arguments
    while (token != NULL && count < MAX_ARGS - 1) {
        args[count] = token;
        count++;
        token = strtok(NULL, " \t\n");
    }
    args[count] = NULL; 
    // execvp needs this NULL at the end
 
    return count;
}
 
// ctime adds a newline at the end, this just chops it off
// so the timestamp fits on the same log line as everything else
void format_time(time_t t, char *out, size_t outsize) {
    char *raw = ctime(&t);
    strncpy(out, raw, outsize - 1);
    out[outsize - 1] = '\0';
 
    size_t len = strlen(out);
    if (len > 0 && out[len - 1] == '\n') {
        out[len - 1] = '\0';
    }
}
 
// forks, execs the command in the child, waits in the parent,
// and logs how long it took
void run_command(const char *original_line, char *args[], FILE *logfile) {
    time_t start_time, end_time;
    char start_str[64], end_str[64];
 
    time(&start_time); // grab time before forking
 
    pid_t pid = fork();
 
    if (pid < 0) {
        perror("fork failed");
        return;
    }
 
    if (pid == 0) {
        // child: become the actual command
        execvp(args[0], args);
 
        // only get here if execvp failed
        fprintf(stderr, "execvp failed for '%s': ", args[0]);
        perror("");
 
        // using _exit here instead of exit -- exit() flushes stdio
        // buffers, and the child has a copy of the parent's
        // logfile buffer from before the fork, so it ends up
        // writing old log lines a second time. _exit skips that.
        _exit(127);
    } else {
        // parent: wait for the child to finish
        int status;
        waitpid(pid, &status, 0);
 
        time(&end_time); // grab time after wait returns
 
        format_time(start_time, start_str, sizeof(start_str));
        format_time(end_time, end_str, sizeof(end_str));
 
        fprintf(logfile, "%s\t%s\t%s\n", original_line, start_str, end_str);
    }
}
 
// main function 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return 1;
    }
    // open the input file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    // open the output log file for writing
    FILE *logfile = fopen("output.log", "w");
    if (logfile == NULL) {
        // if we can't open the log file, close the input file and exit
        printf("Could not open output.log\n");
        fclose(file);
        return 1;
    }
    // read each line from the input file, parse it, and run the command
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file) != NULL) {
        // skip blank lines
        char check[MAX_LINE];
        strncpy(check, line, sizeof(check) - 1);
        check[sizeof(check) - 1] = '\0';
        if (strtok(check, " \t\n") == NULL) {
            continue;
        }
 
        // save the original line before strtok chews it up,
        // since we still need it for the log
        char original_line[MAX_LINE];
        // copy the line into original_line, ensuring null termination
        strncpy(original_line, line, sizeof(original_line) - 1);
        // ensure null termination
        original_line[sizeof(original_line) - 1] = '\0';
        // remove the newline from the end of the original line
        size_t len = strlen(original_line);
        if (len > 0 && original_line[len - 1] == '\n') {
            original_line[len - 1] = '\0';
        }
        // parse the line into an array of arguments
        char *args[MAX_ARGS];
        parse_line(line, args);
        // run the command and log the times
        run_command(original_line, args, logfile);
    }
    // close the files
    fclose(file);
    fclose(logfile);
 
    return 0;
}