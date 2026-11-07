#include <stdio.h>
#include <string.h>
#include "types.h"
#include "common.h"
#include "decode.h"
#include "encode.h"

/* Do encoding
 * Input: struct pointer
 * Output: Success or Failure
 * Description: Decoding all data from encoded img file
 */
Status do_decoding(DecodeInfo *decInfo)
{ 
    printf("INFO: Decoding secret file size\n");
    if(decode_secret_file_size(decInfo) != 0)
    {
        printf("ERROR: Decode secret file size\n");
        return e_failure;
    }
    printf("INFO: Successful\n");
    printf("INFO: Decoding secret file data\n");
    if(decode_secret_file_data(decInfo) != 0)
    {
        printf("ERROR: Decode secret file data\n");
        return e_failure;
    }
    printf("INFO: Decoding Successful\n");
    return e_success;
}

/* Read & validate args of file names
 * Input: argv and struct pointer
 * Output: Success or Failure
 * Description: Reads arguments and 
 * fills the file names required for decoding
 */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    // Check for bmp File
    if(argv[2] == NULL)
    {
        printf("ERROR: Bmp File is not provided\n");
        return e_failure;
    }
    char *cptr = argv[2];
    while(*cptr != '.')
        cptr++;
    if(strcmp(cptr, ".bmp") != 0)
    {
        printf("ERROR: File is not bmp file\n");
        return e_failure;
    }

    decInfo->stego_image_fname = argv[2];
    
    // Check for o/p File
    if(argv[3] == NULL)
    {
        printf("INFO: Output File is not provided\n");
        printf("INFO: Using default o/p File name\n");
        decInfo->secret_fname = "decoded_secret.txt";
        return e_success;
    }
    decInfo->secret_fname = argv[3];

    return e_success;
}

/* Decode magic string
 * Input: struct pointer
 * Output: Success or Failure
 * Description: Reads the magic string from encoded file
 */
Status decode_magic_string(DecodeInfo *decInfo)
{
    int magic_string_size=0; //variable for storing magic string size
    char ch;
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);
    for(int i=31;i>=0;i--)
    {    
        ch = fgetc(decInfo->fptr_stego_image);
        if((ch&1)!=0)
        {
            magic_string_size|=(1<<i);
        }
    }

    char magic_string[magic_string_size+1];
    for(int j=0;j<magic_string_size;j++)
    {
        ch = 0;
        fread(decInfo->image_data, 1, 8, decInfo->fptr_stego_image);
        decode_byte_from_lsb(&ch, decInfo->image_data);
        magic_string[j] = ch;
    }
    magic_string[magic_string_size] = '\0';
    if(strcmp(magic_string, "#*")!=0)
    {
        printf("ERROR: Magic string\n");
        return e_failure;
    }

    return e_success;
}

/* Decode secret file size
 * Input: struct pointer
 * Output: Success or Failure
 * Description: Decodes secret file size from encoded file
 */
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    unsigned ch;
    decInfo->size_l = 0;
    if(decInfo->fptr_stego_image == NULL)
    {
        printf("ERROR: decode_secret_file_size\n");
        return e_failure;
    }
    fseek(decInfo->fptr_stego_image, 134, SEEK_SET);
    for(int i=63;i>=0;i--)
    {
        ch = fgetc(decInfo->fptr_stego_image);
        if((ch&1)!=0)
        {
            decInfo->size_l|=(1L<<i);
        }
    }
    return e_success;
}

/* Open files for decoding
 * Input: struct pointer
 * Output: Success or Failure
 * Description: Opens required files for decoding
 */
Status sopen_files(DecodeInfo *decInfo)
{
    // Decoded secret.txt file
    decInfo->fptr_secret = fopen(decInfo->secret_fname, "wb");
    // Do Error handling
    if(decInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->secret_fname);

        return e_failure;
    }
    
    // Stego Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");
    // Do Error handling
    if (decInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

/* Decode secret file data
 * Input: struct pointer
 * Output: Success or Failure
 * Description: decodes secret file data from encoded file
 */
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    if(decInfo->size_l == 0)
    {
        printf("ERROR: Decode secret file size\n");
        return e_failure;
    }

    for(int i=0; i<(int)decInfo->size_l; i++)
    {
        char ch=0;
        fread(decInfo->image_data, 1, 8, decInfo->fptr_stego_image);
        decode_byte_from_lsb(&ch, decInfo->image_data);
        fputc(ch, decInfo->fptr_secret); 
    }
    return e_success;
}

/* Decode byte from LSB
 * Input: char pointer and struct pointer
 * Output: Success or Failure
 * Description: Decode byte from LSB of encoded img
 * and store it in character
 */
Status decode_byte_from_lsb(char *data, char *data_buffer)
{
    unsigned char cha;
    if(data_buffer == NULL)
    {
        printf("ERROR: data buffer in decode from LSB\n");
        return e_failure;
    }
    for(int i=7;i>=0;i--)
    {
        cha= *data_buffer;
        if((cha&(1))!=0)
        {
            (*data)|=(1<<i);
        }
        data_buffer++;
    }
    return e_success;
}

