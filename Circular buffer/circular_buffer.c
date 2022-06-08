#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

#define SUCCESS 0
#define WRONG_DATA 1
#define ALLOC_ERROR 2

int circular_buffer_create(struct circular_buffer_t *a, int N){
    if(a==NULL || N<1)return WRONG_DATA;

    a->begin = 0;
    a->end = 0;
    a->full = 0;
    a->capacity = N;

    if((a->ptr = (int *) calloc(sizeof(int), N)) == NULL)return ALLOC_ERROR;
    return SUCCESS;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if(cb ==NULL || N<=0)return WRONG_DATA;
    if((*cb = malloc(sizeof(struct circular_buffer_t))) == NULL)return ALLOC_ERROR;

    switch(circular_buffer_create(*cb,N)){
        case 1:
            circular_buffer_destroy_struct(cb);
            return WRONG_DATA;
        case 2:
            circular_buffer_destroy_struct(cb);
            return ALLOC_ERROR;

    };
    return SUCCESS;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a!=NULL && a->ptr != NULL)free(a->ptr);
}


void circular_buffer_display(const struct circular_buffer_t *a){
    if(a ==NULL || a->ptr==NULL || a->begin<0 || a->end<0 || a->begin>=a->capacity || a->end>= a->capacity ||  circular_buffer_empty(a) )return;
    int i = a->begin;
    if (a->full)
    {
        printf("%d ", *(a->ptr + i));
        i = (i + 1) % a->capacity;
    }
    for (; i != a->end; i = (i + 1) % a->capacity)printf("%d ", *(a->ptr + i));
    printf("\n");

}

void circular_buffer_destroy_struct(struct circular_buffer_t **cb) {
    if (cb != NULL)
    {
        circular_buffer_destroy(*cb);
        free(*cb);
    }
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if(a ==NULL || a->ptr==NULL || a->begin<0 || a->end<0 || a->begin>=a->capacity || a->end>= a->capacity)
    {
        if(err_code!=NULL)*err_code = WRONG_DATA;
        return WRONG_DATA;
    }
    int returnValue = 0;
    if(err_code!=NULL)*err_code = SUCCESS;
    if(circular_buffer_empty(a)){
        if(err_code!=NULL)*err_code = ALLOC_ERROR;
        return ALLOC_ERROR;
    }else{
        returnValue = *(a->ptr+a->begin);
        a->begin++;
        if (a->begin == a->capacity) {
            a->begin = 0;
        }
        a->full = 0;
    }
    return returnValue;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){

    if(a ==NULL || a->ptr==NULL || a->begin<0 || a->end<0 || a->begin>=a->capacity || a->end>= a->capacity)
    {
        if(err_code!=NULL)*err_code = WRONG_DATA;
        return WRONG_DATA;
    }

    int returnVal = 0;
    if(err_code!=NULL)*err_code = SUCCESS;
    if(circular_buffer_empty(a)){
        if(err_code!=NULL)*err_code = ALLOC_ERROR;
        return ALLOC_ERROR;
    }
    int move = a->end-1;
    move = move< 0? a->capacity+move : move;
    returnVal = *(a->ptr+move);
    a->end--;
    if(a->end <0){a->end = a->capacity-1;}
    a->full = 0;
    return returnVal;
 }

 int circular_buffer_empty(const struct circular_buffer_t *a){
    if(a==NULL || (a ==NULL || a->ptr==NULL || a->begin<0 || a->end<0 || a->begin>=a->capacity || a->end>= a->capacity)) return -1;
    return (a->begin == a->end) && (a->full==0)? 1 :0;
}

int circular_buffer_full(const struct circular_buffer_t *a){
    if(a==NULL || (a ==NULL || a->ptr==NULL || a->begin<0 || a->end<0 || a->begin>=a->capacity || a->end>= a->capacity)) return -1;
    return (a->begin == a->end) && (a->full!=0)? 1 :0;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if(cb==NULL || (cb ==NULL || cb->ptr==NULL || cb->begin<0 || cb->end<0 || cb->begin>=cb->capacity || cb->end>= cb->capacity))
    {
        return WRONG_DATA;
    }

    if (circular_buffer_full(cb)) {
        *(cb->ptr + cb->end) = value;
        cb->end++;
        cb->begin++;
        if (cb->end == cb->capacity) {
            cb->end = 0;
            cb->begin = 0;
        }
    } else {
        *(cb->ptr + cb->end) = value;
        cb->end++;
        if (cb->end == cb->capacity) {
            cb->end = 0;
        }
        if (cb->begin == cb->end) {
            cb->full = 1;
        }
    }
    return SUCCESS;
}


