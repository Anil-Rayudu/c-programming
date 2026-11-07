// preprocessor statement
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void listContacts(AddressBook *addressBook) 
{
    int choice; //for storing choice
    Contact temp; //temporary Contact struct for swapping
    int size = addressBook->contactCount;
    printf("1. sort by name\n");
    printf("2. sort by phonenumber\n");
    printf("3. sort by email\n");
    printf("Enter the choice : ");
    scanf("%d", &choice);
    getchar(); //for collecting buffer
    switch(choice){
        case 1: 
            /*sorting contacts by name
             *comparing two contacts using strcmp function
             *swapping contacts if it is greater
             */
            for(int i=0; i<size-1; i++){
                for(int j=0; j<size-i-1; j++){
                    if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name)>0){
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
                break;

        case 2: 
            /*sorting contacts by phone number*/
            for(int i=0; i<size-1; i++){
                for(int j=0; j<size-i-1; j++){
                    if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone)>0){
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
                break;

        case 3: 
            /*sorting contacts by email*/
            for(int i=0; i<size-1; i++){
                for(int j=0; j<size-i-1; j++){
                    if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email)>0){
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
                break;
        default:
        {
            printf("Invalid input\n");
            return;
        }
    }
    /*listing all contacts*/
    for(int i=0; i<size; i++){
        printf("%-20s      %10s     %-30s \n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    // addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int check_phoneno(AddressBook *addressBook, char *phone){
    int len;
    len = strlen(phone);

    /*validating phone number is 10 digit number or not*/
    if(len!=10){
        printf("Error : Enter the 10 digit number\n");
        return 0;
    }

    /*checking whether the contact is present in addressbook or not*/
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(phone,addressBook->contacts[i].phone)==0){
            printf("The phone number is already present, so we can't add this contact.\n");
            return 0;
        }
    }
    return 1;
}

int valid_email(char *mail){
    int i=0, count = 0; //variable for counting number of occurance of char '@'
    char sub_str[]= ".com"; //char array of substring for validation
    
    /* check for presence of one @ char in mail id*/
    while(mail[i]!='\0'){
        if(mail[i++]=='@')
            count++;
    }
    if(count != 1){
        printf("please, Enter a Valid email\n");
        return 0;
    }
    if(strstr(mail,sub_str)==NULL){
        printf("please, Enter a Valid email\n");
        return 0;
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    char name[20], phone[20], email[50];//char arrays for storing the name, phonenumber, email
    getchar();
    printf("Enter the name : ");
    scanf("%[^\n]", name);
    getchar();

    /*looping till the valid phone number is provided*/
    do{
        printf("Enter the phone number : ");
        scanf("%s", phone);
    }while(check_phoneno(addressBook, phone)!=1);
    
    /*looping till the valid email input*/
    do{
    printf("Enter the email : ");
    scanf("%s", email);
    }while(valid_email(email)!=1);

    /* copying all details to addressBook*/
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    (addressBook->contactCount)++; //increment contact count
}

void searchContact(AddressBook *addressBook) 
{
    /* logic for search */
    int choice, flag = 0; //variable for choice and flag for noting change
    char name[50];
    char phone[20];
    char email[50];

    printf("1. search by name\n");
    printf("2. search by phonenumber\n");
    printf("3. search by email\n");
    printf("Enter the choice : ");
    scanf("%d", &choice);
    getchar();
    switch(choice){
        case 1: 
            /*Searching the contact by name*/
            printf("Enter the name : ");
            scanf("%[^\n]",name);
            getchar();

            /*comparing entered name with addressBook names and listing out all details if present else print not present*/
            for(int i=0; i< addressBook->contactCount; i++){
                if((strcmp(name, addressBook->contacts[i].name))==0)
                {
                    printf("%s  %s  %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag =1;
                }
            }
            if(flag == 0){
                printf("name is not present in my contact book\n");
            }
        break;

        case 2: 
            /*search by phone number*/
            printf("Enter the phonenumber : ");
            scanf("%[^\n]",phone);
            getchar();
            /*comparing entered phonenumber with addressBooks phone and listing out all details if present else print not present*/
            for(int i=0; i< addressBook->contactCount; i++){
                if((strcmp(phone, addressBook->contacts[i].phone))==0)
                {
                    printf("%s  %s  %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag =1;
                }
            }
            if(flag == 0){
                printf("phone number is not present in my contact book\n");
            }

        break;

        case 3: 
            /*search by email*/
            printf("Enter the email : ");
            scanf("%[^\n]",email);
            getchar();

            /*comparing entered email with addressBook emails and listing out all details if present else print not present*/
            for(int i=0; i< addressBook->contactCount; i++){
                if((strcmp(email, addressBook->contacts[i].email))==0)
                {
                    printf("%s  %s  %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag =1;
                }
            }
            if(flag == 0){
                printf("email is not present in my contact book\n");
            }
        break;
        default:
            printf("Invalid input\n");
    }
}

void editContact(AddressBook *addressBook)
{
	int option; //for storing the option chose
    int index, flag =0; //variable for storing index, flag 
    int count = 0; //for counting the duplicate values
    char name[20], phone[20], email[50]; //char array for storing name, phone, email
    
    printf("Choose the method for Selecting the contact : \n" );
    printf("1. Search by name\n" );
    printf("2. Search by phone number\n");
    printf("3. Search by email id\n");
    printf("Enter the option : ");
    scanf("%d", &option);
    getchar();

    switch(option){
        case 1:
        /*search by name*/
        do{
            printf("enter the name : ");
            scanf("%[^\n]",name);
            getchar();

            /*comparing entered name with addressBook names and listing out all details if present else print not present*/
            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(name,addressBook->contacts[i].name)) ==0){
                    index = i;
                    printf("%d %s  %s  %s\n",i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag = 1;
                    count++;
                }
            }
            if(count>1){
                printf("Enter the  index : ");
                scanf("%d",&index);
                getchar();
            }
            if(flag ==0)
                printf("The name is not present in the contact book, enter the correct one\n");
        }while(flag==0);
        break;
        case 2:
        /*search by phone number*/
        do{
            printf("enter the phone number : ");
            scanf("%[^\n]",phone);
            getchar();
            flag = 0;

            /*comparing entered phone number with addressBook phone numbers and listing out all details if present else print not present*/
            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(phone,addressBook->contacts[i].phone)) ==0){
                    index = i;
                    flag = 1;
                    break;
                }
            }
            if(flag ==0)
                printf("The phone number is not present in the contact book, enter the correct one\n");
        }while(flag==0);

        break;
        case 3:
        /*search by email*/
        do{
            printf("enter the email : ");
            getchar();
            flag = 0;
            scanf("%[^\n]",email);
            getchar();

            /*comparing entered email with addressBook emails and listing out all details if present else print not present*/
            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(email,addressBook->contacts[i].email)) ==0){
                    index = i;
                    flag = 1;
                    break;
                }
            }
            if(flag ==0)
                printf("The email id is not present in the contact book, enter the correct one\n");
        }while(flag==0);
        break;

        default:
        {
            printf("Invalid input\n");
            return;
        }
    }
    option = 0;//using same option for taking the input
    printf("1. Edit the name\n");
    printf("2. Edit the phone number\n");
    printf("3. Edit the email\n");
    printf("4. Edit all\n");
    printf("Enter the option: ");
    scanf("%d", &option);
    getchar();
    switch (option)
    {
    case 4:
        /*Fall through condition for editing all*/
    case 1:
        /*Edit the name*/
        printf("Enter the name : ");
        scanf("%[^\n]",name);
        getchar();
        strcpy(addressBook->contacts[index].name, name);
        if(option !=4)
            break;
    case 2:
        /*Edit the phone number*/
        do{
            printf("Enter the phone number : ");
            scanf("%s", phone);
            getchar();
        }while(check_phoneno(addressBook, phone)!=1);
        
        strcpy(addressBook->contacts[index].phone, phone);
        if(option != 4)
            break;
    case 3:
        /*Edit the email*/
        do{
            printf("Enter the email : ");
            scanf("%s", email);
            getchar();
        }while(valid_email(email)!=1);
        
        strcpy(addressBook->contacts[index].email, email);
        if(option!=4)
            break;
    
    default:
        printf("Invalid input\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
	int option, index =0, flag =0, count = 0;// variables for storing the option, index, changes
    char name[20], phone[20], email[50];//char array for storing name, phone number, email
    printf("Choose the method for Select the contact : \n" );
    printf("1. Search by name\n" );
    printf("2. Search by phone number\n");
    printf("3. Search by email id\n");
    printf("Enter the option : ");
    scanf("%d", &option);
    getchar();
    switch(option){
        case 1:
        /*search by name*/
        do{
            printf("enter the name : ");
            
            scanf("%[^\n]",name);
            getchar();
            
            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(name,addressBook->contacts[i].name)) ==0){
                    index = i;
                    flag = 1;
                    printf("%d %s  %s  %s\n",i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    count++;
                }
            }
            if(count>1){
                printf("Enter the Index : ");
                scanf("%d", &index);
            }
            if(flag ==0)
                printf("The name is not present in the contact book, enter the correct one\n");
        }while(flag==0);
        break;
        case 2:
        /*search by phone number*/
        do{
            printf("enter the phone number : ");
            getchar();
            scanf("%[^\n]",phone);

            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(phone,addressBook->contacts[i].phone)) ==0){
                    index = i;
                    flag = 1;
                    break;
                }
            }
            if(flag ==0)
                printf("The phone number is not present in the contact book, enter the correct one\n");
        }while(flag==0);

        break;
        case 3:
        /*search by email*/
        do{
            printf("enter the email : ");
            getchar();
            scanf("%[^\n]",email);

            for(int i=0; i<addressBook->contactCount;i++){
                if((strcmp(email,addressBook->contacts[i].email)) ==0){
                    index = i;
                    flag = 1;
                    break;
                }
            }
            if(flag ==0)
                printf("The emailid is not present in the contact book, enter the correct one\n");
        }while(flag==0);

        default:
        {
            printf("Invalid input");
            return;
        }
    }
    /*moving all contacts to one index from deleted contact */
    for(int i=index;i<addressBook->contactCount;i++){
        addressBook->contacts[i] = addressBook -> contacts[i+1];
    }
    /*decrementing count after delete contact*/
    (addressBook->contactCount)--;
    printf("Contact deleted Successfully\n");
}
