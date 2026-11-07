/*
name : Anil kumar Rayudu
date : 12/12/2025
description : program to implement fragments using Array of Pointers
sample input : 
sample output :
*/

// preprocessor statements
#include <stdio.h>
#include <stdlib.h>

// function declarations
int fragments(int, float *[]);

// fragments function definition
// int fragments(int row, float *ptr[row]){
//     printf("Before sorting output is:\n");
//     for(int i=0;i<row;i++)
//     {
//         for(int j=0;j<=col[i];j++)
//         {
//             printf("%f ", ptr[i][j]);
//         }
//         printf("\n");
//     }
    
// }

// main function
int main()
{
    int row;
    printf("Enter no.of rows : ");
    scanf("%d", &row);
    int col[row];
    for(int i=0;i<row;i++)
    {
        printf("Enter no of columns in row[%d] : ", i);
        scanf("%d", &col[i]);
    }
    
    // Dynamically allocating for memory for columns
    float *ptr[row];
    for(int i=0;i<row;i++)
    {
        ptr[i] = malloc((col[i]+1)*sizeof(float));
    }
    
    // Read the elements for each row
    for(int i=0;i<row;i++)
    {
        printf("Enter %d values for row[%d] : ", col[i], i);
        for(int j=0;j<col[i];j++)
        {
            scanf("%f", &ptr[i][j]);
        }
    }
    
    // Finding the average and store average values
    for(int i=0;i<row;i++)
    {
        float sum = 0;
        for(int j=0;j<col[i];j++)
        {
            sum+=ptr[i][j];
        }
        ptr[i][col[i]] = sum/col[i];
    }
    
    printf("Before sorting output is:\n");
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<=col[i];j++)
        {
            printf("%f ", ptr[i][j]);
        }
        printf("\n");
    }
    
    for(int i=0;i<row;i++)
    {   
        for(int j=0;j<row-i-1;j++)
        {        
            if((ptr[j][col[j]])>(ptr[j+1][col[j+1]]))
            {
                float *temp = ptr[j];
                ptr[j] = ptr[j+1];
                ptr[j+1] = temp;

                int tmp = col[j];
                col[j] = col[j+1];
                col[j+1] = tmp;
            }
        }
    }
    
    printf("After sorting output is:\n");
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<=col[i];j++)
        {
            printf("%f ", ptr[i][j]);
        }
        printf("\n");
    }
    
}