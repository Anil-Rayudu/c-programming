/* Preprocessing statements */
#include <stdio.h>
#include "types.h"
#include "common.h"
#include "encode.h"
#include "decode.h"

/* main function start */
int main(int argc, char *argv[])
{
    /* Declaring variables */
    uint oper_type;

    /* Declaration of structures */
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    
    /* Checking operation type */
    oper_type = check_operation_type(argv);

    /* Encoding Part */
    if(oper_type == 0)
    {
        // Checking of minimum args for encoding
        if(argc < 4)
        {
            printf("INFO: Please provide required files as : \n");
            printf("./lsb_steg -e <source.bmp> <secret.txt> [output.bmp]\n");
            return 1;
        }

        // Check args & Fill with filenames
        printf("INFO: Checking args & filenames\n");
        if(read_and_validate_encode_args(argv, &encInfo) != 0)
        {
            return 1;
        }
        else
        {
            printf("INFO: Successful\n");
        }

        // open_files
        printf("INFO: opening required files for encoding\n");
        if (open_files(&encInfo) == e_failure)
        {
            printf("ERROR: %s function failed\n", "open_files" );
            return 1;
        }
        else
        {
            printf("SUCCESS: %s function completed\n", "open_files" );
        }

        // Get_image_size_for_bmp
        encInfo.image_capacity = get_image_size_for_bmp(encInfo.fptr_src_image);
        printf("INFO: Image size = %u\n", encInfo.image_capacity);

        // Get_secret_file_size
        encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);
        printf("INFO: Secret file size = %lu \n", encInfo.size_secret_file);
        
        // Check capacity of image file
        printf("INFO: Checking image capacity for secret msg\n");
        if(check_capacity(&encInfo)!= 0)
        {
            printf("ERROR: Image capacity is not sufficient\n");
            return 1;
        }
        printf("INFO: Successful\n");

        printf("INFO: ## Encoding procedure started ##\n");
        
        // Copy_bmp_header
        printf("INFO: Copying bmp header\n");
        if(copy_bmp_header(encInfo.fptr_src_image, encInfo.fptr_stego_image) != 0)
        {
            printf("ERROR: Copying bmp header\n");
            return 1;
        }
    
        printf("INFO: Successful\n");      

        if(do_encoding(&encInfo) != 0)
        {
            return 1;
        }

        printf("INFO: Encoding Successful\n");
    }

    /* Decoding part */
    else if(oper_type == 1)
    {
        printf("INFO: Validating decoding args\n");
        // Checking of minimum args for encoding
        if(argc < 3)
        {
            printf("INFO: Please provide required files as : \n");
            printf("./lsb_steg -d <encoded.bmp> [output.txt]\n");
            return 1;
        }

        // Check args & Fill with filenames
        printf("INFO: Checking args & filenames\n");
        if(read_and_validate_decode_args(argv, &decInfo) != 0)
        {
            return 1;
        }
        printf("INFO: Successful\n");

        // Opening required files
        printf("INFO: Opening required files\n");
        if (sopen_files(&decInfo) == e_failure)
        {
            printf("ERROR: %s function failed\n", "open_files" );
            return 1;
        }
        else
        {
            printf("SUCCESS: %s function completed\n", "open_files" );
        }
        
        // Decoding Magic string
        printf("INFO: Decoding magic string\n");
        if(decode_magic_string( &decInfo) !=0)
        {
            return 1;
        }
        printf("INFO: Successful\n");

        //test decode
        do_decoding(&decInfo);
    }

    /* Invalid argument */
    else
    {
        printf("ERROR: Operation type\n");
        return 1;
    }
    
    return 0;
}
