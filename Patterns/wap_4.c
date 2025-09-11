/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 4
sample output :
1
2 3
4 5 6
7 8 9 10
*/

#include <stdio.h>

int main() {
    int n,i,j,cnt;
    printf("Enter the number: ");
    scanf("%d", &n);
    cnt = 0;
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            cnt++;
            printf("%d ",cnt);
        }
        printf("\n");
    }

    return 0;
}