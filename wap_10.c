/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print patterns
sample input : 5 , 3
sample output :
n=5		n=3
* * * * *     * * *
* * _ * *     * _ *
* _ * _ *     * * *
* * _ * *
* * * * *
*/

#include <stdio.h>

int main() {

    int n,i,j;
    printf("Enter the number: ");
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i%2==0&&j==n/2+1){
                printf(" ");
            }
            else if(j%2==0&&i==n/2+1){
                printf(" ");
            }
            else{
                printf("*");
            }
        }
        printf("\n");
    }

    return 0;
}