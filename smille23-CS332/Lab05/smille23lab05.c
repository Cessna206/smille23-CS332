/* Sherilyn Miller
CS332
smille23
lab05

Compile : gcc -Wall -o smille23lab05 smille23lab05.c


run: ./lab05 /"directorypath"
remove quotation, leave forward slash


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// returns a string name for the file type
char *filetype(mode_t mode){
    char *str;

    if (S_ISREG(mode)) {
        str = "regular";
    } else if (S_ISDIR(mode)) {
        str = "directory";
    } else if (S_ISCHR(mode)) {
        str = "character special";
    } else if (S_ISBLK(mode)) {
        str = "block special";
    } else if (S_ISFIFO(mode)) {
        str = "fifo";
    } else if (S_ISLNK(mode)) {
        str = "symbolic link";
    } else if (S_ISSOCK(mode)) {
        str = "socket";
    } else {
        str = "unknown?";
    }

    return str;

}

//list one directory then recursively list any subdirectories
void listdir(const char *name, int depth){
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char fullpath[1024];
    int count = 1;

    dir = opendir(name);
    if (dir == NULL) {
        printf("Error opening directory: %s\n", name);
        return;
}

while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries to avoid infinite recursion
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // build the full path to the entry since readdir only gives the name
        snprintf(fullpath, sizeof(fullpath), "%s/%s", name, entry->d_name);
        // get the file status
        // used lstat to show symbolic links as links instead of the file they point to
        if (lstat(fullpath, &statbuf) < 0) {
            printf("Error getting file status: %s\n", fullpath);
            continue;
        }
        // print entry name and type with indentation based on depth
        printf("%*s[%d] %s (%s)\n", depth * 4, "", count, entry->d_name, filetype(statbuf.st_mode));
        count++;
        // If the entry is a directory, recursively list its contents
        if (S_ISDIR(statbuf.st_mode)) {
            listdir(fullpath, depth + 1);
        }
    }
    // close the directory stream
    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *dirpath;

    if (argc < 2) {
        dirpath = ".";
    } else {
        dirpath = argv[1];
    }

    listdir(dirpath, 0);

    return 0;
}