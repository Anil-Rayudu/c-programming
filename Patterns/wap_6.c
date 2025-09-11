/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 4
sample output :
1 2 3 4
1 2 3
1 2
1
*/

#include <stdio.h>

int main() {
    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=n;i>=1;i--){
        for(j=1;j<=i;j++){
            printf("%d ",j);
        }
        printf("\n");
    }

    return 0;
}