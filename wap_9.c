/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 5
sample output :
1 2 3 4 5
6 _ _ 7
8 _ 9
10 11
12
*/

#include <stdio.h>

int main() {
    int n,i,j,cnt;
    printf("Enter the number: ");
    scanf("%d", &n);
    cnt = 0;
    for(i=5;i>=1;i--){
        for(j=1;j<=i;j++){
            if(i==n||j==1||i==j){
                cnt++;
                printf("%d ",cnt);
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }

    return 0;
}