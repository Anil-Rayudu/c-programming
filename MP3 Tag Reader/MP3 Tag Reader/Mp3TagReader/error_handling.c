#include <stdio.h>
#include <string.h>
#include "error_handling.h"

/*
 * To display_error message along with usage
 */
void display_error(const char *message)
{
    printf("ERROR: %s\n", message);
    printf("USAGE:\n");
    printf("To view please pass like : ./mp3tagreader -v mp3filename\n");
    printf("To edit please pass like : ./mp3tagreader -e -t/-T-a/-A/-y/-c/-g changing_text mp3filename\n");
    printf("To get help pass like : ./mp3tagreader -h\n");   
}

int check_id3_tag_presence(const char *filename)
{
    FILE *fptr = fopen(filename, "r");
    char tag[4];
    fread(tag, 3, 1, fptr);
    tag[4] = '\0';
    if(strcmp(tag, "ID3")!=0)
    {
        printf("ERROR: Invalid TAG\n");
        return -1;
    }
    return 0;
}
