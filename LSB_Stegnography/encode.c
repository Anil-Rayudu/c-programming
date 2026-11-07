#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("INFO: width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("INFO: height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* Get text file size
 * Input: file ptr
 * Output: size
 * Description: The file size is position of pointer at EOF
 * size is 4 bytes
 */
uint get_file_size(FILE *fptr)
{   
    uint size;
    // Seek to end of file
    fseek(fptr, -1, SEEK_END);

    // Read the size (an int)
    size = ftell(fptr);
    rewind(fptr);

    // Return size
    return size;
}


/* Checks operation type
 * Input: runtime arguments through argv
 * Output: OpeartionType Encode or Decode or Unsupported
 * Description: Checks the arguments and 
 * returns encode or decode 
 */
OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-e")==0)
    {
        return e_encode;
    }
    else if(strcmp(argv[1],"-d")==0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}

/* Read & validate args of file names
 * Input: argv and struct pointer
 * Output: Success or Failure
 * Description: Reads arguments and 
 * fills the file names required for encoding
 */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
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

    encInfo->src_image_fname = argv[2];
    
    // Check for secret File
    if(argv[3] == NULL)
    {
        printf("ERROR: Secret File is not provided\n");
        return e_failure;
    }
    encInfo->secret_fname = argv[3];

    // Check for o/p File
    if(argv[4] == NULL)
    {
        printf("INFO: Output File is not provided\n");
        printf("INFO: Using default o/p File\n");
        encInfo->stego_image_fname = "stego_img.bmp";
        return e_success;
    }
    encInfo->stego_image_fname = argv[4];

    return e_success;
}

/* Copy bmp header from Src Image file to Dest Image file
 * Input: Src Image file ptr, Dest Image file ptr
 * Output: Header copied Stego Image file
 * Description: In BMP Image, header is upto 54 bytes.
 * Return Value: e_success or e_failure, on errors
 */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    // Check for Src Image file is not NULL
    if(fptr_src_image == NULL)
    {
        printf("Error in Src Image file\n");
        return e_failure;
    }

    /* Check fptr_src_image is pointing to zero
     * if not rewind to pos it to zero */
    if(ftell(fptr_src_image) != 0)
    {
        rewind(fptr_src_image);
    }

    // Loop and copy header till the file ptr reaches 54
    while(ftell(fptr_src_image) != 54)
    {
        char ch = fgetc(fptr_src_image);
        fputc(ch, fptr_dest_image);
    }
    
    return e_success;
}

/* 
 * Get magic string encoded file
 * Inputs: magic string, ptr to EncodeInfo
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    int magic_string_size; // Variable for storing size of magic string
    char ch; // Variable for storing character

    magic_string_size = strlen(magic_string);
    if(magic_string_size == 0)
    {
        printf("ERROR: No magic string\n");
        return e_failure;
    }

    // Encoding magic string size
    for(int i=31; i>=0; i--)
    {
        ch = fgetc(encInfo->fptr_src_image);
        if((magic_string_size&(1<<i)) != 0)
        {
            ch|=1;
        }
        else
        {
            ch&= ~1;
        }
        fputc(ch, encInfo->fptr_stego_image);
    }

    // Encoding magic string    
    for(int j=0; j<magic_string_size;j++)
    {
        fread(encInfo->image_data, 1, 8, encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[j], encInfo->image_data);
        fwrite(encInfo->image_data, 1, 8, encInfo->fptr_stego_image);
    }
    return e_success;
}

/* Encode secret file extension
 * Input: file_extn pointer, structure address
 * Output: Success or Faiure
 * Description: Take src img data, file_extension and 
 * encode file extension and write to output img file
 */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    if(file_extn == NULL)
    {
        printf("ERROR: Encode secret file extn\n");
        return e_failure;
    }
    while((*file_extn)!='.')
        file_extn++;
    strcpy(encInfo->extn_secret_file, file_extn);

    for(int i=0; i<MAX_FILE_SUFFIX; i++)
    {
        fread(encInfo->image_data, 1, 8, encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i], encInfo->image_data);
        fwrite(encInfo->image_data, 1, 8, encInfo->fptr_stego_image); 
    }    
    return e_success;
}

/* Encode secret file size
 * Input: long file_size, structure address
 * Output: Success or Faiure
 * Description: Take src img data, file_extension and 
 * encode secret file size and write to output img file
 */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char ch;
    if(file_size == 0)
    {
        printf("ERROR: Secret file size is zero\n");
        return e_failure;
    }
    
    // Encoding file size
    for(int i=63;i>=0;i--)
    {
        ch = fgetc(encInfo->fptr_src_image);
        if((file_size&((long)1<<i)) != 0)
        {
            ch|=1;
        }
        else
        {
            ch&= ~1;
        }
        fputc(ch, encInfo->fptr_stego_image);
    }
    return e_success;
}

/* Encode secret file size
 * Input: long file_size, structure address
 * Output: Success or Faiure
 * Description: Take src img data, file_extension and 
 * encode secret file size and write to output img file
 */
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    int ch;
    for(int i=0;i<encInfo->size_secret_file;i++)
    {
        ch = getc(encInfo->fptr_secret);
        fread(encInfo->image_data, 1, 8, encInfo->fptr_src_image);
        encode_byte_to_lsb(ch, encInfo->image_data);
        fwrite(encInfo->image_data, 1, 8, encInfo->fptr_stego_image);
    }
    return e_success;
}

/*
 * Encoding byte to LSB 
 * Inputs: character , char pointer to array
 * Output: Success or Failure
 * Description: Encoding character to img data at LSB of 8 bytes
 */
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    if(image_buffer == NULL)
    {
        printf("ERROR: Encode image buffer\n");
        return e_failure;
    }
    
    for(int i=7;i>=0;i--)
    {
        if((data&(1<<i))!=0)
        {
            (*image_buffer)|=1;
        }
        else
        {
            (*image_buffer)&=~1;
        }
        image_buffer++;
    }
    return e_success;
}

/*
 * Copying of remaining image data 
 * Inputs: File pointer source, File pointer Destination
 * Output: Success or Failure
 * Description: copying remaining data character by character
 */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    unsigned char ch;
    if(fptr_src == NULL)
    {
        printf("ERROR: Source file pointer\n");
        return e_failure;
    }
    while(!feof(fptr_src))
    {
        ch=fgetc(fptr_src);
        fputc(ch, fptr_dest);
    }
    return e_success;
}


/*
 * Do encoding 
 * Inputs: Structure pointer
 * Output: Success or Failure
 * Description: Encoding of all the data in image
 */
Status do_encoding(EncodeInfo *encInfo)
{
    printf("INFO: Encoding Magic string\n");
    if(encode_magic_string(MAGIC_STRING, encInfo) != 0)
    {
        printf("ERROR: Encoding Magic string\n");
        return e_failure;
    }
    printf("INFO: Successful\n");

    printf("INFO: Encoding secret file extension\n");
    if(encode_secret_file_extn(encInfo->secret_fname, encInfo) != 0)
    {
        printf("ERROR: Encoding secret file extension\n");
        return e_failure;
    }
    printf("INFO: Successful\n");

    printf("INFO: Encoding secret file size\n");
    if(encode_secret_file_size(encInfo->size_secret_file, encInfo) != 0)
    {
        printf("ERROR: Encoding secret file extension\n");
        return e_failure;
    }
    printf("INFO: Successful\n");

    printf("INFO: Encoding secret file data\n");
    if(encode_secret_file_data(encInfo) != 0)
    {
        printf("ERROR: Encoding secret file data\n");
        return e_failure;
    }
    printf("INFO: Successful\n");

    printf("INFO: Copying remaining img data\n");
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) != 0)
    {
        printf("ERROR: Copying remaining img data\n");
        return e_failure;
    }
    printf("INFO: Successful\n");

    return e_success;
}


/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

/* Check capacity of image file
 * Input: Structure pointer
 * Output: Success or Failure
 * Description: Check for image file capacity for
 * encoding secret file
 */
Status check_capacity(EncodeInfo *encInfo)
{
    if(encInfo->image_capacity<(8*(encInfo->size_secret_file)+200)){
        printf("ERROR: file capacity is small to encode the data\n");
        return e_failure;
    }
    else
        return e_success;
}


