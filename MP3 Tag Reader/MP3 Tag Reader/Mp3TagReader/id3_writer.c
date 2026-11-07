/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */
int write_id3_tags(const char *filename, const TagData *data) {
    // Implementation for writing ID3 tags
    FILE *fptr = fopen(filename, "w");
    fseek(fptr, 3, SEEK_SET);
    fprintf(fptr, "%s", data->version);
    printf("%ld\n", ftell(fptr));
    return 0;
}

/** TODO: Add documentation as sample given above */
int edit_tag(const char *filename, const char *tag, const char *value) {
    char tags[5];
    unsigned int size;
    char buff[30];
    TagData *data = read_id3_tags(filename);
    if (!data) {
        return 1;
    }
    // Implementation for writing ID3 tags to file
    FILE *fptr = fopen(filename, "r+");
    fseek(fptr, 10, SEEK_SET);

    if (strcmp(tag, "-t")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "TIT2")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    else if (strcmp(tag, "-a")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "TPE1")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    else if (strcmp(tag, "-A")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "TALB")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    else if (strcmp(tag, "-y")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "TYER")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    else if (strcmp(tag, "-c")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "COMM")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    else if (strcmp(tag, "-g")==0)
    {
        while(fread(tags, 4, 1, fptr))
        {
            size = 0;
            tags[4] = '\0';
            printf("%s\n", tag);
            fread(buff, 4, 1, fptr);
            size |= (((unsigned int)buff[0])<<24);
            size |= (((unsigned int)buff[1])<<16);
            size |= (((unsigned int)buff[2])<<8);
            size |= ((unsigned int)buff[3]);
            buff[0] = '\0';
            fseek(fptr, 2, SEEK_CUR);
            if(strcmp(tags, "TCON")==0)
            {
                long int tmp = ftell(fptr);
                printf("%ld", tmp);
                fseek(fptr, tmp, SEEK_SET);
                printf("%ld", ftell(fptr));
                fwrite(value, sizeof(char), size, fptr);
                fseek(fptr, tmp, SEEK_SET);
                return 0;
            }
            else
            {
                fseek(fptr, size, SEEK_CUR);
            }
            tags[0]='\0';
        }
    }
    return -1;
}
