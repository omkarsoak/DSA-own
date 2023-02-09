#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 1; i < (2 * n); i++)
    {
        for (int j = 1; j < (2 * n); j++)
        {
            printf("%d ", n - (i+1)/2);
        }
        printf("\n");
    }
    return 0;
}