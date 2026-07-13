/* Sherilyn Miller
CS332
smille23
lab06

This program reads in the file listings.csv, stores every row in a
struct listing, and then sorts the data two ways for the homework:
  1) alphabetically by host_name
  2) numerically by price
Each sorted version gets written out to its own new csv file.

Compile : gcc -Wall -o lab06 smille23lab06.c

run: ./lab06 listings.csv
if no filename is given, it defaults to listings.csv in the current directory
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max characters we expect on any one line of the csv file
#define LINESIZE 1024
// max number of rows/listings we can hold the sample file is small
// so 30000 gives us plenty of room to work with
#define MAX_LISTINGS 30000

// define a struct to hold one row of the csv file.
// The csv has 13 columns so the struct has 13 members, split up by
// whether they are ints, floats, or strings (char*).
struct listing {
    int id, host_id, minimum_nights, number_of_reviews,
        calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

// this array is where we keep all the listings once we read them in
struct listing list_items[MAX_LISTINGS];
int count = 0;   // keeps track of how many listings we actually read

// takes one line of text from the csv file and breaks it up
// using strtok, then stuffs each piece into the right struct member.
// strtok is called once with the line, then every call after that
// uses NULL to keep grabbing tokens from the same string.
 
struct listing getfields(char *line) {
    struct listing item;

    item.id                             = atoi(strtok(line, ","));
    item.host_id                        = atoi(strtok(NULL, ","));
    item.host_name                      = strdup(strtok(NULL, ","));
    item.neighbourhood_group            = strdup(strtok(NULL, ","));
    item.neighbourhood                  = strdup(strtok(NULL, ","));
    item.latitude                       = atof(strtok(NULL, ","));
    item.longitude                      = atof(strtok(NULL, ","));
    item.room_type                      = strdup(strtok(NULL, ","));
    item.price                          = atof(strtok(NULL, ","));
    item.minimum_nights                 = atoi(strtok(NULL, ","));
    item.number_of_reviews              = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365               = atoi(strtok(NULL, ","));

    return item;
}

// just prints one listing to the screen
void displayStruct(struct listing item) {
    printf("%d,%d,%s,%s,%s,%.5f,%.5f,%s,%.2f,%d,%d,%d,%d\n",
           item.id, item.host_id, item.host_name, item.neighbourhood_group,
           item.neighbourhood, item.latitude, item.longitude, item.room_type,
           item.price, item.minimum_nights, item.number_of_reviews,
           item.calculated_host_listings_count, item.availability_365);
}

// same idea as displayStruct but writes to a file instead of the screen
void writeStruct(FILE *fptr, struct listing item) {
    fprintf(fptr, "%d,%d,%s,%s,%s,%.5f,%.5f,%s,%.2f,%d,%d,%d,%d\n",
            item.id, item.host_id, item.host_name, item.neighbourhood_group,
            item.neighbourhood, item.latitude, item.longitude, item.room_type,
            item.price, item.minimum_nights, item.number_of_reviews,
            item.calculated_host_listings_count, item.availability_365);
}

//Comparator functions for qsort. qsort needs a function that returns
 //negative/zero/positive depending on how the two elements compare

int compareByHostName(const void *a, const void *b) {
    struct listing *listA = (struct listing *) a;
    struct listing *listB = (struct listing *) b;
    return strcmp(listA->host_name, listB->host_name);
}

// compares two listings by price (cheapest first)
int compareByPrice(const void *a, const void *b) {
    struct listing *listA = (struct listing *) a;
    struct listing *listB = (struct listing *) b;

    // can't just subtract floats and cast to int,
    // so do it the safe way with if statements
    if (listA->price < listB->price) return -1;
    if (listA->price > listB->price) return 1;
    return 0;
}

int main(int argc, char *argv[]) {

    // let the user pass in a filename, otherwise just default to
    // listings.csv like the lab example does
    char *filename = "listings.csv";
    if (argc > 1) {
        filename = argv[1];
    }

    //open the file for reading only
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Could not open %s, exiting.\n", filename);
        return 1;
    }

    char line[LINESIZE];

    // grab the first line to check if it's a header row 
    // if it is a header, we just skip it and keep going
    fgets(line, LINESIZE, fptr);
    if (strncmp(line, "id,", 3) != 0) {
        rewind(fptr);   // wasn't a header, so go back to the start
    }

    //loop through the rest of the file line by line and
    // parse each one into the array of structs
    while (fgets(line, LINESIZE, fptr) != NULL) {
        // fgets keeps the newline character, so chop it off
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 0) {
            continue;   // skip any blank lines
        }

        list_items[count] = getfields(line);
        count++;
    }

    fclose(fptr);

    printf("Read in %d listings from %s\n\n", count, filename);

    // print out the first few rows just to make sure everything
    // was read in correctly
    printf("First 5 rows read in:\n");
    for (int i = 0; i < count && i < 5; i++) {
        displayStruct(list_items[i]);
    }

  
    // make a copy of the array first for each sort so that sorting by price doesn't mess
    // up the order we need for sorting by host_name

    struct listing sortedByHostName[MAX_LISTINGS];
    memcpy(sortedByHostName, list_items, count * sizeof(struct listing));
    qsort(sortedByHostName, count, sizeof(struct listing), compareByHostName);

    struct listing sortedByPrice[MAX_LISTINGS];
    memcpy(sortedByPrice, list_items, count * sizeof(struct listing));
    qsort(sortedByPrice, count, sizeof(struct listing), compareByPrice);

    // write the host_name sorted results to a new file
    FILE *outHostName = fopen("sorted_by_host_name.csv", "w");
    if (outHostName == NULL) {
        printf("Could not open sorted_by_host_name.csv for writing.\n");
        return 1;
    }
    fprintf(outHostName, "id,host_id,host_name,neighbourhood_group,neighbourhood,"
                          "latitude,longitude,room_type,price,minimum_nights,"
                          "number_of_reviews,calculated_host_listings_count,availability_365\n");
    for (int i = 0; i < count; i++) {
        writeStruct(outHostName, sortedByHostName[i]);
    }
    fclose(outHostName);
    printf("\nWrote sorted_by_host_name.csv\n");

    // write the price sorted results to a new file
    FILE *outPrice = fopen("sorted_by_price.csv", "w");
    if (outPrice == NULL) {
        printf("Could not open sorted_by_price.csv for writing.\n");
        return 1;
    }
    fprintf(outPrice, "id,host_id,host_name,neighbourhood_group,neighbourhood,"
                       "latitude,longitude,room_type,price,minimum_nights,"
                       "number_of_reviews,calculated_host_listings_count,availability_365\n");
    for (int i = 0; i < count; i++) {
        writeStruct(outPrice, sortedByPrice[i]);
    }
    fclose(outPrice);
    printf("Wrote sorted_by_price.csv\n");

    // free up all the strings we strdup'd earlier so we don't leak memory

    for (int i = 0; i < count; i++) {
        free(list_items[i].host_name);
        free(list_items[i].neighbourhood_group);
        free(list_items[i].neighbourhood);
        free(list_items[i].room_type);
    }

    return 0;
}