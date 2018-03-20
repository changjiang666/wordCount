#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wc.h"
#include "file.h"
#include "help.h"

#define DEBUG 0

#define FALSE 0
#define TRUE  1
#define ALL 1
#define PART 0

#define MAX_PATH 100

#define PROCESS     if(c_state == TRUE)\
                        printf("%s, 字符数:%d\n", path[j], info->nc);\
                    if(w_state == TRUE)\
                        printf("%s, 单词数:%d\n", path[j], info->nw);\
                    if(l_state == TRUE)\
                        printf("%s, 行数:%d\n", path[j], info->nl);\
                    if(a_state == TRUE)\
                        printf("%s,  代码行/空行/注释行:%d/%d/%d\n", path[j], \
                               info->codeline, info->spaceline, info->commentline);



int
main(int argc, char **argv)
{
    #if DEBUG
    int argc = 5;
    char *argv[5];
    argv[1] = "-c";
    argv[2] = "test.c";
    argv[3] = "-e";
    argv[4] = "stop.txt";
    #endif // DEBUG

    /*state val*/
    /*i, j use for loop val*/
    int i, j = 0;
    /*array path to store file path, p visit command line*/
    char *path[MAX_PATH] , *p, *filename;
    /*buffer store .c file*/
    char *buffer;
    /*maintain a struct to store statistic info*/
    BasicInfo *info;
    /*process_type 0 represent single file*/
    int process_type;
    /*mask word list*/
    char **word_list;
    /*word_list path*/
    char *word_list_path;
    /*word buffer*/
    char *buf;
    /*state val to capture command line parameter*/
    int c_state, w_state, l_state, s_state, a_state;


    /*initialize val and parse command line parameter*/
    word_list_path = path[0] = p = filename = NULL;
    process_type = PART;
    c_state = w_state = l_state = s_state = a_state = FALSE;
    #if !DEBUG
    if(1 == argc)
    {
        printf("Please Open In CMD!\n\n\n\nAt CMD, Enter 'wc.exe -help' For More Help!\n\n\n");
        system("pause");
        return EXIT_FAILURE;
    }
    #endif
    for(i = 1; i < argc; ++i)
    {
        p = argv[i];

        /*capture -s*/
        if(strcmp(p, "-s") == 0)
            s_state = TRUE;

        /*capture -a*/
        if(strcmp(p, "-a") == 0)
            a_state = TRUE;

        if(strcmp(p, "-c") == 0)
            c_state = TRUE;
        if(strcmp(p, "-w") == 0)
            w_state = TRUE;
        if(strcmp(p, "-l") == 0)
            l_state = TRUE;
        if(strcmp(p, "-help") ==0)
        {
            help();
            return EXIT_SUCCESS;
        }


        /*loop until p point to '\0'*/
        while(*++p != NULL)
            ;

        /*p go back 2 char and compare to ".c"
          in order to identify the path name*/
        if(strcmp(p - 2, ".c") == 0)
            path[j++] = argv[i];


        /*p go back 4 char and compare to ".txt", at the same time argv[i - 1]
        stores "-e", so we can identify the word_list path and check user valid input*/
        if(strcmp(p - 4, ".txt") == 0 && strcmp(argv[i - 1],"-e") == 0 )
        {
            word_list_path = argv[i];
        }

        /*p go back 4 char and compare to ".txt", at the same time argv[i + 1]
        stores null pointer, so we can identify the file name*/
        if(strcmp(p - 4, ".txt") == 0 && argv[i + 1] == '\0')
        {
            /*if lack of "-o" before file name, throw error information*/
            if(strcmp(argv[i - 1], "-o") == 0)
                filename = argv[i];
            else
            {
                if(strcmp(argv[i - 1], "-e") != 0)
                {
                    printf("command line error.\n");
                    return EXIT_FAILURE;
                }

            }
        }
    }
    /*imitate DOS, add a '\0' after the last parameter*/
    path[j] = '\0';
    /*j > 1 means user input *.c, so change process_type"*/
    if(j > 1)
    {
        if(s_state == TRUE)
            process_type = ALL;
        else
            {
                printf("command line error.\n");
                return EXIT_FAILURE;
            }
    }
    if(word_list_path != NULL)
    {
        /*read word_list to buffer*/
        buf = readfile(word_list_path);
        /*process buffer and get a two-dimensional pointer*/
        word_list = processBuf(buf);
    }
    else
    {
        word_list = (char **)malloc(sizeof(char *));
        word_list[0] = '\0';
    }


    /*process exception*/
    if(path[0] == NULL)
    {
        printf("command line error.\n");
        return EXIT_FAILURE;
    }


    /*process command line and redirection*/
    if (filename == NULL)
            filename = "result.txt";
    freopen(filename, "w", stdout);


    /*loop process each path*/
    j = 0;
    while(path[j] != '\0')
    {
        buffer = readfile(path[j]);
        info = CWL(buffer, word_list, a_state);
        PROCESS;
        free(info);
        free(buffer);
        ++j;
    }
    return EXIT_SUCCESS;
}
