#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * decoding secret file from encoded Image file
 * Info about output and intermediate data is
 * also stored
 */

typedef struct _DecodeInfo
{
    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;
    long size_l;
    char image_data[9];

    /* Secret file Info */
    char *secret_fname;
    FILE *fptr_secret;

} DecodeInfo;

/* Performing the decoding */
Status do_decoding(DecodeInfo *decInfo);

/* Read & validate decode args */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Decode Magic String */
Status decode_magic_string(DecodeInfo *decInfo);

/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status sopen_files(DecodeInfo *decInfo);

/* Decode a byte from LSB of image data array */
Status decode_byte_from_lsb(char *data, char *data_buffer);

/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo);

#endif