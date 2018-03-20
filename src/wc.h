#ifndef WC_H_
#define WC_H_

typedef struct BasicInfo
{
    int nc;     //char
    int nw;     //word
    int nl;     //line
    int codeline;
    int spaceline;
    int commentline;
}BasicInfo;


BasicInfo *CWL(char const *buf, char const **word_list, int a_state);

#endif // WC_H_
