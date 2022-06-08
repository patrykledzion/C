//
// Created by patry on 06.09.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "matrix_utils.h"
#include <string.h>

int matrix_create(struct matrix_t *m, int width, int height)
{
    if(m==NULL || width<1 || height<1)return 1;
    m->ptr = malloc(height * sizeof(int *));
    if(m->ptr==NULL)
    {
        free(m->ptr);
        return 2;
    }
    for(int i=0;i<height;i++)
    {
        *(m->ptr+i) = (int*)malloc(width * sizeof(int));
        if((void *) *(m->ptr + i) == NULL)
        {
            for(int j=0;j<=i;j++)free((void *) *(m->ptr + j));
            free(m->ptr);
            return 2;
        }
    }
    m->width = width;
    m->height = height;
    return 0;
}

int matrix_read(struct matrix_t *m)
{
    if(m==NULL)return 1;
    if(m->height<1 || m->width<1 || m->ptr==NULL)return 1;

    for(int i=0;i<m->height;i++)
    {
        for(int j=0;j<m->width;j++)
        {
            int temp;
            if(!scanf("%d",&temp))return 2;

            *(*(m->ptr+i)+j) = temp;
        }
    }
    return 0;
}
void matrix_display(const struct matrix_t *m)
{
    if(m==NULL)return;
    if(m->ptr==NULL || m->height<1 || m->width<1)return;
    for(int i=0;i<m->height;i++)
    {
        for(int j=0;j<m->width;j++)
        {
            printf("%d ",*(*(m->ptr+i)+j));
        }
        printf("\n");
    }
}
void matrix_destroy(struct matrix_t *m) {
    if (m == NULL)return;
    if (m->ptr == NULL)return;
    for (int i = 0; i < m->height;i++)
    {
        if(*m->ptr+i!=NULL)free(*(m->ptr+i));
    }
    free(m->ptr);
}

struct matrix_t* matrix_create_struct(int width, int height)
{
    if(width<1 || height<1)return NULL;
    struct matrix_t *s = malloc(sizeof(struct matrix_t));
    if(s==NULL)return NULL;
    int test;
    test = matrix_create(s,width,height);
    if(test!=0)
    {
        free(s);
        return NULL;
    }
    return s;
}

void matrix_destroy_struct(struct matrix_t **m)
{
    if(m==NULL)return;
    matrix_destroy(*m);
    free(*m);
    *m = NULL;
}

struct matrix_t* matrix_copy(struct matrix_t *m)
{
    if(m==NULL || m->width<1 || m->height<1 ||m->ptr==NULL)return NULL;
    struct matrix_t *cpy = matrix_create_struct(m->width,m->height);
    if(cpy==NULL)return NULL;
    for(int i=0;i<m->height;i++)
    {
        for(int j=0;j<m->width;j++)
        {
            *(*(cpy->ptr+i)+j) = *(*(m->ptr+i)+j);
        }
    }

    return cpy;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<1 || m1->height<1 || m2->width<1 || m2->height<1)return NULL;
    if(m1->width != m2->width || m1->height != m2->height)return NULL;
    struct matrix_t *sum = matrix_create_struct(m1->width,m1->height);
    if(sum==NULL)return NULL;
    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m2->width;j++)
        {
            *(*(sum->ptr+i)+j) = *(*(m1->ptr+i)+j) + *(*(m2->ptr+i)+j);
        }
    }

    return sum;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<1 || m1->height<1 || m2->width<1 || m2->height<1)return NULL;
    if(m1->width != m2->width || m1->height != m2->height)return NULL;
    struct matrix_t *sum = matrix_create_struct(m1->width,m1->height);
    if(sum==NULL)return NULL;
    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m2->width;j++)
        {
            *(*(sum->ptr+i)+j) = *(*(m1->ptr+i)+j) - *(*(m2->ptr+i)+j);
        }
    }

    return sum;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<1 || m1->height<1 || m2->width<1 || m2->height<1)return NULL;
    if(m1->width!=m2->height)return NULL;
    int width,height;
    width = m2->width;
    height = m1->height;

    struct matrix_t *multiply = matrix_create_struct(width,height);
    if(multiply==NULL)return NULL;
    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m2->width;j++)
        {
            *(*(multiply->ptr+i)+j)=0;
            for(int k=0;k<m1->width;k++)
            {
                //multiply->ptr[i][j] += m1->ptr[i][k] * m2->ptr[k][j];
                *(*(multiply->ptr+i)+j)+=*(*(m1->ptr+i)+k) * *(*(m2->ptr+k)+j);
            }
        }
    }
    return multiply;
}

struct matrix_t* matrix_load_b(const char *filename, int *err_code)
{
    if(err_code!=NULL)*err_code = 0;
    if(filename==NULL)
    {
        if(err_code!=NULL)*err_code = 1;
        return NULL;
    }

    FILE *f = fopen(filename,"rb");
    if(f==NULL)
    {
        if(err_code!=NULL)*err_code = 2;
        return NULL;
    }

    int width,height;
    int test = 0;
    test+=(int)fread(&width,sizeof(int),1,f);
    test+=(int)fread(&height,sizeof(int),1,f);
    if(test<2)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 3;
        return NULL;
    }
    if(width<1 || height<1)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 3;
        return NULL;
    }
    struct matrix_t *m = matrix_create_struct(width,height);

    if(m==NULL)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 4;
        return NULL;
    }

    for(int i=0;i<height;i++)
    {
        test = (int)fread(*(m->ptr+i),sizeof(int),width,f);
        if(!test)
        {
            fclose(f);
            matrix_destroy_struct(&m);
            if(err_code!=NULL)*err_code = 3;
            return NULL;
        }
    }
    fclose(f);
    return m;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code)
{
    if(err_code!=NULL)*err_code = 0;
    if(filename==NULL)
    {
        if(err_code!=NULL)*err_code = 1;
        return NULL;
    }

    FILE *f = fopen(filename,"r");
    if(f==NULL)
    {
        if(err_code!=NULL)*err_code = 2;
        return NULL;
    }

    int width,height;

    int test = 0;
    test+=(int)fscanf(f,"%d",&width);
    test+=(int)fscanf(f,"%d",&height);
    if(test<2)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 3;
        return NULL;
    }

    if(width<1 || height<1)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 3;
        return NULL;
    }

    struct matrix_t *m = matrix_create_struct(width,height);
    if(m==NULL)
    {
        fclose(f);
        if(err_code!=NULL)*err_code = 4;
        return NULL;
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int temp;
            test = fscanf(f,"%d",&temp);
            if(!test)
            {
                fclose(f);
                matrix_destroy_struct(&m);
                if(err_code!=NULL)*err_code = 3;
                return NULL;
            }

            *(*(m->ptr+i)+j) = temp;
            if(j<width-1 && feof(f))
            {
                fclose(f);
                matrix_destroy_struct(&m);
                if(err_code!=NULL)*err_code = 3;
                return NULL;
            }
        }

    }

    fclose(f);
    return m;
}

int type_of_file(char *filename)
{
    if(filename==NULL)return -1;
    char a1,a2,a3,a4;
    a1 = *(filename+strlen(filename)-1);
    a2 = *(filename+strlen(filename)-2);
    a3 = *(filename+strlen(filename)-3);
    a4 = *(filename+strlen(filename)-4);

    if(a4=='.' && a3=='b' && a2=='i' && a1=='n')return 0;
    else if(a4=='.' && a3=='t' && a2=='x' && a1=='t')return 1;
    return -1;
}
