#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"


#define ALLOC_ERROR 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define M_INC_INP "Incorrect input\n"
#define M_INC_INP_D "Incorrect input data\n"
#define M_F_ALL_MEM "Failed to allocate memory\n"




int main()
{
    struct circular_buffer_t *cb;
    int size;
    printf("Podaj pojemnosc buffora: ");
    if(!scanf("%d",&size))
    {
        printf("%s",M_INC_INP);
        return INCORRECT_INPUT;
    }

    if(size<1)
    {
        printf("%s",M_INC_INP_D);
        return INCORRECT_INPUT_DATA;
    }

    if(circular_buffer_create_struct(&cb, size) == 2)
    {
        printf("%s",M_F_ALL_MEM);
        return ALLOC_ERROR;
    }

    choice_mark:{
        int choice;
        printf("Co chcesz zrobic: ");
        if(!scanf("%d",&choice))
        {
            printf("%s",M_INC_INP);
            circular_buffer_destroy_struct(&cb);
            return INCORRECT_INPUT;
        }

        switch(choice)
        {
            case 1:{
                int val;
                printf("Podaj liczbe: ");
                if(!scanf("%d",&val))
                {
                    printf("%s",M_INC_INP);
                    circular_buffer_destroy_struct(&cb);
                    return INCORRECT_INPUT;
                }

                circular_buffer_push_back(cb, val);
                break;}
            case 2:{
                int err_code, val;
                val = circular_buffer_pop_back(cb, &err_code);
                if (err_code == 0)printf("%d\n", val);
                else printf("Buffer is empty\n");
                break;}
            case 3:{
                int err_code, val;
                val = circular_buffer_pop_front(cb, &err_code);
                if (err_code == 0)printf("%d\n", val);
                else printf("Buffer is empty\n");
                break;}
            case 4:{
                if (circular_buffer_empty(cb))printf("Buffer is empty\n");
                else circular_buffer_display(cb);
                break;}
            case 5:{
                printf("%d\n", circular_buffer_empty(cb));
                break;}
            case 6:{
                printf("%d\n", circular_buffer_full(cb));
                break;}
            case 0:
                circular_buffer_destroy_struct(&cb);
                return 0;
            default:
                printf("%s",M_INC_INP_D);
                break;
        }
        goto choice_mark;
    }

    circular_buffer_destroy_struct(&cb);


}
