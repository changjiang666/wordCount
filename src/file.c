#include "file.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define FILE_NUM    100
#define USELSEE_NUM 100
#define WORD_LEN 30


/*
**function:return the length of file
**parameter:file pointer
*/
static int
filelength(FILE *fp)
{
    int num;
    fseek(fp, 0, SEEK_END);
    num = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return num;
}


/*
**function:read file to buffer
**parameter:file path,relative or absolute path
*/
char *
readfile(char const *path)
{
    FILE *fp;
    int len;
    char *buf;

    if((fp = fopen(path, "r")) == NULL)
    {
        printf("open file %s error.\n", path);
        exit(0);
    }


    len = filelength(fp);
    buf = (char *) malloc (len);
    fread(buf, sizeof(char), len, fp);
    fclose(fp);
    *(buf + len - 1) = '\0';
    return buf;
}



/*
**function:return all file names at current path
*/
char **
getDir(void)
{
    //initialize val
    int i, j = 0;
    FILE *fp;
    char **buf = (char **) malloc(sizeof(char *) * FILE_NUM);
    for(i = 0; i < FILE_NUM; ++i)
        buf[i] = (char *) malloc (sizeof(char) * BUFSIZ);

    //get current path file
    system("if exist file_list.txt, del file_list.txt");
    system("dir *.c/b >> file_list.txt");

    //read file_list to buffer
    i = 0;
    if((fp = fopen("file_list.txt", "r")) == NULL)
    {
         printf("open file_list.txt error.\n");
         exit(0);
    }
    while(!feof(fp))
    {
        j = 0;
        memset(buf[i], 0, BUFSIZ - 1);
        fgets(buf[i], BUFSIZ - 1, fp);
        while(buf[i][j] != '\n')
           ++j;
        buf[i][j] = '\0';
        ++i;
    }
    buf[i] = '\0';
    fclose(fp);

    return buf;
}


char **
processBuf(char const *buf)
{
    char **word_list;
    int i;
    word_list = (char **) malloc(sizeof(char *) * USELSEE_NUM);
    for(i = 0; i < USELSEE_NUM; ++i)
        word_list[i] = (char *) malloc(sizeof(char) * WORD_LEN);


    i = 0;
    char seps[] = ",\t\n ";
    char *token;
    token = strtok(buf, seps);
    while(token != NULL )
    {
        strcpy(word_list[i++], token);
        token = strtok(NULL, seps);
    }
    word_list[i] = '\0';


//    i = 0;
//    while(word_list[i] != '\0')
//        printf("%s\n", word_list[i++]);

    return word_list;
}


