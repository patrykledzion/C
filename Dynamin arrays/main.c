#include <stdio.h>
#include <stdlib.h>

int create_array_int(int **ptr, int N)
{
    if(!N || N <= 0 || ptr==NULL) return 1;
    *ptr=(int*)malloc(N*sizeof(int));
    if(*ptr==NULL) return 2;
    return 0;
}

void destroy_array_int(int **ptr)
{
    if(ptr)
    {
        free(*ptr);
        *ptr=NULL;
    }
}

int main()
{
    int size,val;
    int *ptr;
    printf("Podaj rozmiar: ");
    if(!scanf("%d",&size))
    {
        printf("Incorrect input");
        return 1;
    }
    if(size<1)
    {
        printf("Incorrect input data");
        return 2;
    }
    val=create_array_int(&ptr, size);
    if(val==1)
    {
        printf("Incorrect input");
        destroy_array_int(&ptr);
        return 1;
    }
    if(val==2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i=0;i<size; i++)
    {
        if(scanf("%d",ptr+i)!=1)
        {
            printf("Incorrect input");
            destroy_array_int(&ptr);
            return 1;
        }
    }
    for(int i=size-1;i>=0;i--)
    {
        printf("%i ",*(ptr+i));
    }
    destroy_array_int(&ptr);
    return 0;
}
