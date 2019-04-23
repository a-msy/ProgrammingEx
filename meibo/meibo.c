/* 
 * File:   meibo.c
 * Author: 09430509
 *
 * Created on 2019/04/10
 * update on 2019/04/19
 */

#include <stdio.h>

#define LIMIT 1024

int subst(char *str,char c1,char c2);

int split(char *str,char *ret[],char sep,int max);
void testprint_split(char *str);
void error_split(int check);

int get_line(char *input);
void testprint_get_line();

static int maxsplit = 5;

int main(void){
    char test1[] = "";//分割したい文字列
    char test2[] = ",,,";
    char test3[] = ",oka,yama";
    char test4[] = "o,ka,ya,,ma,a";
    char *ret[maxsplit];//分割後に入れる文字配列個数
    char input[LIMIT+1];
    
    testprint_split(test1);
    testprint_split(test2);
    testprint_split(test3);
    testprint_split(test4);

    testprint_get_line(input);
    
    return 0;

}

int subst(char *str,char c1,char c2){
    int count = 0;
    while(*str != '\0'){
        if(*str == c1){
            *str = c2;
            count++;
        }
        str++;
    }
    return count;
}

int split (char *str,char *ret[],char sep,int max){
    int count = 0;//分割数

    while (1) {
        if(*str == '\0') {
            break;//からもじなら抜ける
        }
       
        ret[count++] = str;//strをいじればretも変わるように分割後の文字列にはポインタを入れる

        while( (*str != '\0') && (*str != sep) ){//区切り文字が見つかるまでポインタすすめる 
            str++;
        }
        
        if(*str == '\0') {
            break;//区切り文字がなかったら抜ける＝文字列はそのまま
        }                                                                                                   

        *str = '\0';//必ず区切り文字のはずだからくぎる
	    str++;//インクリメントさせる  
    }
    //if(count<max) count = -1;
    if(count>max)count = -2;
    error_split(count);
    
    return count;
}

void error_split(int check){
    switch(check){
        case -1:
            printf("luck.\n");
            break;
        
        case -2:
            printf("over.\n");
            break;
        
        default:
            break;
    }
    return;
}

void testprint_split(char *str){
    int count;
    char *ret[maxsplit];
    
    printf("test %s\n",str);
    
    count=split(str,ret,',',maxsplit);
    
    for(int i = 0; i < count; i++){
        printf("%d:%s\n",i+1, ret[i]);
    }
    
    printf("count is %d.\n\n",count);
    return;
}

int get_line(char *input){

    if (fgets(input, LIMIT + 1, stdin) == NULL || input[0] == '\n'){//何かしら入力させて、改行のみは認めない
        printf("error:NULL or input is \\n.\n");
        return 0; /* 失敗EOF */
    }

    subst(input, '\n', '\0');
    return 1; /*成功*/

}

void testprint_get_line(char *input){
    int n = 0;

    printf("input line:");
    while (get_line(input)) {
        printf("*** line %d:\n", ++n);
        testprint_split(input);
        printf("input line:");
    }
    return;
}