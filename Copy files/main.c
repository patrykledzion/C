#include <stdio.h>
#include <stdarg.h>

int error(int err_code,char *err)
{
    if(err!=NULL)return !printf("%s",err) + err_code;
    switch(err_code)
    {
        case 1: printf("Incorrect input");break;
        case 2: printf("Incorrect input data");break;
        case 4: printf("Couldn't open file");break;
        case 5: printf("Couldn't create file");break;
        //case 8: printf("Failed to allocate memory");break;
        case 9: printf("Not enough arguments");break;
        default: printf("Incorrect error code");break;
    }
    return err_code;
}

int main(int argc, char **argv) {
    if (argc <= 2)return error(9,NULL);
    char buffer;
    FILE *file1 = fopen(*(argv + 1), "rb");
    if (file1 == NULL)return error(4,NULL);
    FILE *file2 = fopen(*(argv + 2), "wb");
    if (file2 == NULL)
    {
        fclose(file1);
        return error(5,NULL);
    }
    while (!feof(file1)) {
        fread(&buffer, 1, 1, file1);
        if (!feof(file1))fwrite(&buffer, 1, 1, file2);
    }
    fclose(file1);
    fclose(file2);
    printf("File copied");
    return 0;
}