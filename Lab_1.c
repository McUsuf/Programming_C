#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_KEY 16
#define BLOCK_SIZE 500

void check(unsigned char *source,  unsigned char *key, int count, int shift){
    while ((*(source+count) == *(key+count))&&(count > 0)){
        printf("%d ", shift+count);
        --count;
    }
}

int main(){
    unsigned char key[MAX_KEY];
    unsigned char *source=(unsigned char *) malloc(BLOCK_SIZE);
    int table[256];
    int sourceLength,keyLength,j,end;
    int len,mark=0,shift = 0;
    unsigned char lastch,ch;
	if (source==NULL){
        printf("error");
        return 0;
    }
    gets((char *)key);
    keyLength=strlen((char *)key);
    sourceLength=fread(source, sizeof(char), BLOCK_SIZE, stdin);
    int i;
    for(i=0; i<256; ++i){
        table[i]=keyLength;
    }
    for(i = 0; i<keyLength-1; ++i){
        table[key[i]]=keyLength-i-1;
    }
    lastch=key[keyLength-1];
    while ((sourceLength==BLOCK_SIZE)||(mark <= sourceLength-keyLength)){
        if (mark+keyLength > sourceLength){
            end = mark;
            len =  BLOCK_SIZE-end;
            for (j=0; j<len; ++j){
                source[j] = source[len+j];
            }
            sourceLength = fread(source+len, sizeof(char), BLOCK_SIZE-len, stdin) + len;
            shift += BLOCK_SIZE-len;
            mark = 0;
        }
        ch = source[mark+keyLength-1];
        printf("%d ", mark+keyLength+shift);
        if (ch==lastch){
            check(&source[mark], key, keyLength-1, shift+mark);
        }
        mark+=table[ch];
    }
    free(source);
    
	return 0;
}
