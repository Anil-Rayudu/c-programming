/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 5
sample output :
A B C D E
  A B C D
    A B C
      A B
        A
*/

#include <stdio.h>

int main() {
    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        for(j=1;j<i;j++){
            printf("  ");
        }
        for(j=1;j<=n-i+1;j++){
            printf("%c ",64+j);
        }
        printf("\n");
    }

    return 0;
}