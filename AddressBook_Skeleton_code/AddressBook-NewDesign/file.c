// preprocessor statements
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.txt","w");
    int size = addressBook->contactCount;
    fprintf(fptr, "#%d#\n", size);
    for(int i=0; i<size; i++){
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    char str[100]; //char array for storing string
    /*creating file pointer and opening file in readmode*/
    FILE *fptr = fopen("contacts.txt","r");
    if(fptr == NULL){
        printf("File is not present\n");
    }
    else{
        /*from the first line collecting the size of the data present*/
        fscanf(fptr,"%[^\n]",str);
        int size = atoi(strtok(&str[1],"#"));
        addressBook->contactCount = size;
        
        /*using strtok func seperate the details and strcpy function to copy all details to addressbook*/
        for(int i=0; i<size;i++){
            fscanf(fptr, " %[^\n]", str);
            strcpy(addressBook->contacts[i].name, strtok(str,","));
            strcpy(addressBook->contacts[i].phone, strtok(NULL,","));
            strcpy(addressBook->contacts[i].email, strtok(NULL,","));
        }
    }
}
