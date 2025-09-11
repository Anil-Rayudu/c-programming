/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 4
sample output :
4 4 4 4 4 4 4
4 3 3 3 3 3 4
4 3 2 2 2 3 4
4 3 2 1 2 3 4
4 3 2 2 2 3 4
4 3 3 3 3 3 4
4 4 4 4 4 4 4
*/

#include <stdio.h>

int main() {
    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=n;i>=1;i--){
        for(j=n;j>i;j--){
            printf("%d ",j);
        }
        for(j=2;j<=2*i-1;j++){
            printf("%d ",i);
        }
        for(j=i;j<=n;j++){
            printf("%d ",j);
        }
        printf("\n");
    }
    for(i=2;i<=n;i++){
        for(j=n;j>i;j--){
            printf("%d ",j);
        }
        for(j=2;j<=2*i-1;j++){
            printf("%d ",i);
        }
        for(j=i;j<=n;j++){
            printf("%d ",j);
        }
        printf("\n");
    }

    return 0;
}