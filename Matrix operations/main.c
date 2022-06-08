#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matrix_utils.h"

void clear (void)
{
    while ( getchar() != '\n' );
}

int main() {


    char *filename1 = malloc(20);
    if(filename1==NULL)return 8+!printf("Failed to allocate memory");
    printf("Podaj nazwe 1 pliku: ");
    scanf("%19s",filename1);

    struct matrix_t *m1;
    int err_code;
    if(type_of_file(filename1)==0)m1 = matrix_load_b(filename1,&err_code);
    else if(type_of_file(filename1)==1)m1 = matrix_load_t(filename1,&err_code);
    else
    {
        free(filename1);
        return 7+!printf("Unsupported file format");
    }
    if(m1==NULL)
    {
        free(filename1);
        if(err_code==2)return 4+!printf("Couldn't open file");
        else if(err_code==3)return 6+!printf("File corrupted");
        else if(err_code==4)return 8+!printf("Failed to allocate memory");
        return -1;
    }
    free(filename1);
    clear();
    char *filename2 = malloc(20);
    if(filename2==NULL)
    {
        return 8+!printf("Failed to allocate memory");
    }
    printf("Podaj nazwe 2 pliku: ");
    scanf("%19s",filename2);


    err_code = 0;
    struct matrix_t *m2;
    if(type_of_file(filename2)==0)m2 = matrix_load_b(filename2,&err_code);
    else if(type_of_file(filename2)==1)m2 = matrix_load_t(filename2,&err_code);
    else {
        free(filename2);
        matrix_destroy_struct(&m1);
        return 7+!printf("Unsupported file format");
    }
    if(m2==NULL)
    {
        free(filename2);
        matrix_destroy_struct(&m1);
        if(err_code==2)return 4+!printf("Couldn't open file");
        else if(err_code==3)return 6+!printf("File corrupted");
        else if(err_code==4)return 8+!printf("Failed to allocate memory");
        return -1;
    }
    free(filename2);
    clear();
    struct matrix_t *sum = matrix_add(m1,m2);
    struct matrix_t *sub = matrix_subtract(m1,m2);
    struct matrix_t *mult = matrix_multiply(m1,m2);
    if(sum==NULL)printf("Error\n");
    else matrix_display(sum);
    if(sub==NULL)printf("Error\n");
    else matrix_display(sub);
    if(mult==NULL)printf("Error\n");
    else matrix_display(mult);

    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);
    matrix_destroy_struct(&sum);
    matrix_destroy_struct(&sub);
    matrix_destroy_struct(&mult);

}
