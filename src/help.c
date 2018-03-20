#include "help.h"
#include <windows.h>

void
help(void)
{
    printf("\ndemo: wc.exe -a -s -c -w -l *.c -e stoplist.txt -o output.txt\n");
    printf("\nFor More, view this blog!\n");
    ShellExecute(NULL, NULL, "iexplore", "http://www.cnblogs.com/ningjing-zhiyuan/p/8563562.html", NULL, SW_SHOW);
}
