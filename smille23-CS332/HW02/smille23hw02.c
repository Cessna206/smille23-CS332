#include <stdio.h>      // standard i/o
#include <stdlib.h>     // ascii to int/long in
#include <string.h>     // string compare/substring
#include <dirent.h>     // directory reading
#include <sys/stat.h>   // lstat, struct stat and S_ISDIR
#include <time.h>       // local time, strftime
#include <libgen.h>     // basename
#include <unistd.h>     // getopt


// filter for cli reading
typedef struct {
    long s_limit;
    char *f_pattern;
    int f_depth;
} filter_ctx;

//function pointer types for search and print functions
typedef int (*search_func)(const char *name, int depth, off_t size, filter_ctx *ctx);
typedef void (*print_func)(const char *name, const struct stat *sb, int depth);

//checks for -s
int match_size(const char *name, int depth, off_t size, filter_ctx *ctx) {
    // matching search_func's unused parameters to avoid compiler warnings
    (void)name; (void)depth;
    return (size <= ctx->s_limit);
}

//checks for -f
int match_pattern_depth(const char *name, int depth, off_t size, filter_ctx *ctx) {
    // matching search_func's unused parameters to avoid compiler warnings
    (void)size;
    return (depth <= ctx->f_depth && strstr(name, ctx->f_pattern) != NULL);
}

//check is filters match
// check filters every time regardless of their precense. return 
// everything if no filters are present. return 0 if any filter fails, 1 if all filters pass
int matches_all(const char *name, int depth, off_t size, filter_ctx *ctx, search_func filters[], int num_filters) {
    for (int i = 0; i < num_filters; i++) {
        if (!filters[i](name, depth, size, ctx)) {
            return 0; // If any filter does not match, return false
        }
    }
    return 1; // All filters matched
}

//bit mask to write permissions
void mode_to_perm_string(mode_t mode, char *buf){
    buf[0] = S_ISDIR(mode) ? 'd' : '-';
    buf[1] = (mode & S_IRUSR) ? 'r' : '-';
    buf[2] = (mode & S_IWUSR) ? 'w' : '-';
    buf[3] = (mode & S_IXUSR) ? 'x' : '-';
    buf[4] = (mode & S_IRGRP) ? 'r' : '-';
    buf[5] = (mode & S_IWGRP) ? 'w' : '-';
    buf[6] = (mode & S_IXGRP) ? 'x' : '-';
    buf[7] = (mode & S_IROTH) ? 'r' : '-';
    buf[8] = (mode & S_IWOTH) ? 'w' : '-';
    buf[9] = (mode & S_IXOTH) ? 'x' : '-';
    buf[10] = '\0';
}

// file tpype analysis function to return a string representation of the file type based on the mode
char *filetype(mode_t mode){
    if (S_ISREG(mode)) return "regular file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISCHR(mode)) return "character device";
    if (S_ISBLK(mode)) return "block device";
    if (S_ISFIFO(mode)) return "FIFO/pipe";
    if (S_ISLNK(mode)) return "symlink";
    if (S_ISSOCK(mode)) return "socket";
    return "unknown";
}

// PRINTING //

void print_indent(int depth){
    for (int i = 0; i < depth; i++) {
        printf("\t"); // two spaces per depth level
    }
}


// basic print function to print the name and file type of a file
void print_basic(const char *name, const struct stat *sb, int depth) {
    (void)sb; // unused parameter
    print_indent(depth);
    printf("%s\n", name);
}

void print_long(const char *name, const struct stat *sb, int depth){
    // force directory size to 0 for printing
    long long size = S_ISDIR(sb->st_mode) ? 0 : (long long)sb->st_size;
    // convert mode to permission string for pritning
    char perms[11];
    mode_to_perm_string(sb->st_mode, perms);
    // convert time to human readable format for printing
    char timebuf[64];
    struct tm *tm_info = localtime(&sb->st_atime);
    // format time as YYYY-MM-DD HH:MM:SS
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    
    print_indent(depth);
    printf("%s %s %lld %s\n", perms, timebuf, size, name);
}


// SEARCHING //

// recursive function to search a directory and its subdirectories for files matching the filters
void search_directory(const char *dir_path, int depth, filter_ctx *ctx, search_func filters[], int num_filters, print_func print) {
    // Open the directory
    DIR *dir = opendir(dir_path);
    //error handling for directory opening
    if (dir == NULL){
        printf("Error opening directory %s\n", dir_path);
        return;
    }
    // struct for reading directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        // Get file information using lstat
        struct stat statbuffer;
        if (lstat(full_path, &statbuffer) < 0) {
            printf("lstat error for %s\n", full_path);
            continue;
        }

        // Calculate the depth of the current entry
        int entry_depth = depth + 1;
        off_t size = S_ISDIR(statbuffer.st_mode) ? 0 : statbuffer.st_size;

        // Check if the entry matches all filters
        if (matches_all(entry->d_name, entry_depth, size, ctx, filters, num_filters)) {
            print(entry->d_name, &statbuffer, entry_depth);
        }

    
        // If it's a directory and we haven't reached the max depth, recurse into it
        if (S_ISDIR(statbuffer.st_mode)) {
            search_directory(full_path, entry_depth, ctx, filters, num_filters, print);
        }
    }

    closedir(dir);
}
// function to get the root label of the directory path
void get_root_label(const char *dirpath, int explicit_path, char *out, size_t outsize) {
    char buf[1024];
    if (explicit_path) {
        strncpy(buf, dirpath, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';
    } else {
        if (getcwd(buf, sizeof(buf)) == NULL) {
            strncpy(buf, ".", sizeof(buf) - 1);
        }
    }
    char *base = basename(buf);
    strncpy(out, base, outsize - 1);
    out[outsize - 1] = '\0';
}

// main function to parse command line arguments and initiate the search
int main(int argc, char *argv[]) {
    int flagS = 0, use_s = 0, use_f = 0;
    filter_ctx ctx = {0, NULL, 0};
 
    int i = 1;
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-S") == 0) {
            flagS = 1;
            i++;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "-s requires a size in bytes\n");
                exit(1);
            }
            ctx.s_limit = atol(argv[i + 1]);
            use_s = 1;
            i += 2;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 2 >= argc) {
                fprintf(stderr, "-f requires a pattern and a depth\n");
                exit(1);
            }
            ctx.f_pattern = argv[i + 1];
            ctx.f_depth = atoi(argv[i + 2]);
            use_f = 1;
            i += 3;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            fprintf(stderr, "Usage: %s [-S] [-s size] [-f pattern depth] [directory]\n", argv[0]);
            exit(1);
        }
    }
    // Determine the starting directory
    const char *start_dir = (i < argc) ? argv[i] : ".";
    search_func filters[2];
    int num_filters = 0;

        if (use_s) filters[num_filters++] = match_size;
        if (use_f) filters[num_filters++] = match_pattern_depth;


    // Determine the display name for the root of the tree
    char root_label[1024];
get_root_label(start_dir, i < argc, root_label, sizeof(root_label));

    // Check if the starting directory exists and is accessible
    struct stat root_stat;
        if (lstat(start_dir, &root_stat) < 0) {
        printf("Error opening directory %s\n", start_dir);
     return 1;
    }
    printf("%s\n", root_label);

    // Choose the appropriate print function based on the -S flag
    print_func print = flagS ? print_long : print_basic;

    search_directory(start_dir, 0, &ctx, filters, num_filters, print);
        return 0;

}