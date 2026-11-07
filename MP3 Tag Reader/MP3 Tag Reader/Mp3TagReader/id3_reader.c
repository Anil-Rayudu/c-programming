/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "id3_reader.h"
#include "error_handling.h"

/**
 * @param filename 
 * @return Pointer of TagData on success or NULL on failure
 */
TagData* read_id3_tags(const char *filename) {
    // Implementation for reading ID3 tags
    unsigned int size;
    char tag[5];
    char ver[11];
    char buff[30];
    TagData *data;
    data = create_tag_data();
    FILE *fptr = fopen(filename, "r");
    fseek(fptr, 3, SEEK_SET);
    fread(buff, 1, 2, fptr);
    sprintf(ver, "ID3 V2.%x.%x", buff[0], buff[1]);
    data->version = malloc(5 * sizeof(char));
    strcpy(data->version, ver);
    fseek(fptr, 10, SEEK_SET);
    if((strcmp(ver,"ID3 V2.4.0")==0) || (strcmp(ver, "ID3 V2.3.0")==0))
    {
        while(fread(tag, 4, 1, fptr))
        {
            size = 0;
            tag[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            // printf("%d ", size);
            // printf("%x\n", size);
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tag, "TIT2")==0)
            {
                data->title = malloc((size+1) * sizeof(char));
                fread(data->title, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TPE1")==0)
            {
                data->artist = malloc((size+1) * sizeof(char));
                fread(data->artist, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TALB")==0)
            {
                data->album = malloc((size+1) * sizeof(char));
                fread(data->album, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TYER")==0)
            {
                data->year = malloc((size+1) * sizeof(char));
                fread(data->year, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "COMM")==0)
            {
                data->comment = malloc((size+1) * sizeof(char));
                fread(data->comment, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TCON")==0)
            {
                data->genre = malloc((size+1) * sizeof(char));
                fread(data->genre, sizeof(char), size, fptr);
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tag[0]='\0';
        }
    }
    else if(strcmp(ver, "ID3 V2.2.0")==0)
    {
        while(fread(tag, 3, 1, fptr))
        {
            size = 0;
            tag[3] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            // printf("%d ", size);
            // printf("%x\n", size);
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tag, "TT2")==0)
            {
                data->title = malloc((size+1) * sizeof(char));
                fread(data->title, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TOA")==0)
            {
                data->artist = malloc((size+1) * sizeof(char));
                fread(data->artist, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TAL")==0)
            {
                data->album = malloc((size+1) * sizeof(char));
                fread(data->album, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TYE")==0)
            {
                data->year = malloc((size+1) * sizeof(char));
                fread(data->year, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "COM")==0)
            {
                data->comment = malloc((size+1) * sizeof(char));
                fread(data->comment, sizeof(char), size, fptr);
            }
            else if(strcmp(tag, "TCO")==0)
            {
                data->genre = malloc((size+1) * sizeof(char));
                fread(data->genre, sizeof(char), size, fptr);
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tag[0]='\0';
        }
    }
    
    return data;
}

/**
TODO: Add documention as sample given
 */
void display_metadata(const TagData *data) {
    // Implementation for displaying metadata
    printf("------------------SELECTED VIEW DETAILS------------------\n\n");
    printf("---------------------------------------------------------\n");
    printf("            MP3 TAG READER AND EDITOR FOR ID3V2\n");
    printf("---------------------------------------------------------\n");
    printf("VERSION          :  %s\n", data->version);
    printf("TITLE            :  %s\n", data->title);
    printf("ARTIST           :  %s\n", data->artist);
    printf("ALBUM            :  %s\n", data->album);
    printf("YEAR             :  %s\n", data->year);
    printf("COMMENT          :  %s\n", data->comment);
    printf("GENRE            :  %s\n", data->genre);
    printf("---------------------------------------------------------\n\n");
    printf("---------------DETAILS DISPLAYED SUCCESSFULLY--------------\n");
}

/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename) {
    TagData *data = read_id3_tags(filename);
    if (!data) {
        // display_error("Failed to read ID3 tags.");
        return;
    }
    display_metadata(data);
    free_tag_data(data);
}
