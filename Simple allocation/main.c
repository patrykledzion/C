#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main()
{

    int *tab;
    if(!(tab = malloc(sizeof(int)*SIZE)))
    {
        printf("Failed to allocate memory");
        return 8;
    }

    for(int i=0;i<100;i++)
    {
        *(tab+i) = i;
    }

    for(int i=0;i<100;i++)
    {
        printf("%d ",*(tab+i));
    }

    free(tab);
}
