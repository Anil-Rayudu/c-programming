/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 4
sample output :
    1
  2 3 2
3 4 5 4 3
  2 3 2
    1
*/


#include <stdio.h>

int main() {

    int i, j, n, cnt;
    printf("Enter the number: ");
    scanf("%d", &n);
    cnt = 0;
    for(i=1;i<=n;i++){
        for(j=1;j<=n-i;j++){
            printf("  ");
        }
        for(j=1;j<=i;j++){
            cnt++;
            printf("%d ", cnt);
        }
        for(j=2;j<=i;j++){
            cnt--;
            printf("%d ", cnt);
        }
        printf("\n");
    }
    for(i=n-1;i>=1;i--){
        cnt--;
        cnt--;
        for(j=1;j<=n-i;j++){
            printf("  ");
        }
        for(j=1;j<=i;j++){
            cnt++;
            printf("%d ", cnt);
        }
        for(j=2;j<=i;j++){
            cnt--;
            printf("%d ", cnt);
        }
        printf("\n");
    }

    return 0;
}