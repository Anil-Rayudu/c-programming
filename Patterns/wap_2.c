/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 5
sample output :
* * * * *
* * * *
* * *
* *
*
*/

#include <stdio.h>

int main() {
    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=5;i>=1;i--){
        for(j=1;j<=i;j++){
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}