#ifndef FILE_H_
#define FILE_H_


//read file to buffer
char *readfile(char const *path);

//recursion get filename
char **getDir(void);

//process buffer and get mask word
char **processBuf(char const *buf);

#endif // FILE_H_
