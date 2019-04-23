/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * https://qiita.com/fireflower0/items/dc54f3ec1b3698a98b14
 */

#include <stdio.h>

#define true 1
#define false 0

int split(char *str,char *ret[],char sep,int max);

int main(void){
    int max = 1024;
    char test1[] = "";//分割したい文字列
    char test2[] = ",,,";
    char test3[] = "oka,yama";
    char test4[] = ",oka,ya,,ma,";
    char *ret[100];//分割後に入れる文字配列
    
    testprint(test3,ret,',',max);
    
    return 0;
}

void testprint(char *str,char *ret[],char sep,int max){
    int count;
    
    printf("test %s\n",str);
    
    count=split(str,ret,',',max);
    
    for(int i = 0; i < count; i++){
        printf("%d:%s\n",i+1, ret[i]);
    }
    
    printf("count is %d.\n\n",count);
}

int split (char *str,char *ret[],char sep,int max){
    int count = 0;//分割数

    while (1){

        if(*str == '\0') {
            printf("\nend.2\n");
            break;//区切り文字がなかったら抜ける＝文字列はそのまま
        }

        ret[count++] = str;
        printf("ret:%s\n",str);

        while( (*str != '\0') && (*str != sep) ){//区切り文字が見つかるまでポインタすすめる 
            printf("debug:%c-6\n",*str);
            str++;
        }

        printf("\nfind split char.3\n"); 
        if(*str == '\0') {
            printf("\nend4\n");
            break;//区切り文字がなかったら抜ける＝文字列はそのまま
        }

        *str++ = '\0';//となりは必ず区切り文字のはず
    }
    return count;
}
