/*
name : Anil kumar Rayudu
Date : 04/09/2025
Description : program to print negative fibonacci numbers
sample input : -8
sample output : 0 1 -1 2 -3 5 -8

*/

#include <stdio.h>

int main() {

    int num;
    int p=0, q=1;
    int sum = p-q;
    printf("Enter the number: ");
    scanf("%d", &num);
    while (p>=-num&&p<=num||p<=-num&&p>=num){
        printf("%d ",p);
        p=q;
        q=sum;
        sum = p-q;
    }

    return 0;
}