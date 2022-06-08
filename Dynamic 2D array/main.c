#include <stdio.h>
#include <stdlib.h>


#define ALLOC_ERROR 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define M_INC_INP "incorrect input\n"
#define M_INC_INP_D "Incorrect input data\n"
#define M_F_ALL_MEM "Failed to allocate memory\n"


int **create_array_2d(int width, int height)
{
    if(width<1 || height <1) return NULL;
    int **tab = (int **)malloc(height * sizeof(int *));
    if(!tab)return NULL;

    for(int i=0;i<height;i++)
    {
        *(tab + i) = (int *)malloc(width * sizeof(int));
        if(*(tab+i)==NULL)
        {
            for(int j=0;j<=i;j++)free(*(tab + j));
            free(tab);
            return NULL;
        }

    }

    return tab;


}

void destroy_array_2d(int **ptr, int height)
{
    if(ptr==NULL)return;
    if(height < 1)return;

    for(int i=0;i<height;i++)free(*(ptr + i));
    free(ptr);
}

void display_array_2d(int **ptr, int width, int height)
{
    if(ptr == NULL)return;
    if(width<1 || height<1)return;

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            printf("%d ",*(*(ptr+i)+j));
        }
        printf("\n");
    }
}


int main()
{
    int **tab;
    int width,height;
    printf("Podaj rozmiar tablicy (W x H): ");
    if(!scanf("%d",&width)) return !printf("%s",M_INC_INP) + INCORRECT_INPUT;
    if(!scanf("%d",&height)) return !printf("%s",M_INC_INP) + INCORRECT_INPUT;
    if(width < 1 || height < 1)return !printf("%s",M_INC_INP_D) + INCORRECT_INPUT_DATA;


    tab = create_array_2d(width,height);

    if(tab==NULL)return !printf("%s",M_F_ALL_MEM) + ALLOC_ERROR;

    printf("Podaj liczby: ");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int val;
            if(!scanf("%d",&val))
            {
                destroy_array_2d(tab,height);
                return !printf("%s",M_INC_INP) + INCORRECT_INPUT;
            }
            *(*(tab+i)+j) = val;
        }

    }

    display_array_2d(tab,width,height);

    destroy_array_2d(tab,height);


}
