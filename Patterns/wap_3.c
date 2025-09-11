/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 5
sample output :
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
*/

#include <stdio.h>

int main() {
    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            printf("%d ",j);
        }
        printf("\n");
    }

    return 0;
}