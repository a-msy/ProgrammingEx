/* 
 * File:   main.c
 * Author: 09430509
 *
 * Created on 2019/04/10
 * update on 2019/04/10
 */

#include <stdio.h>

int subst(char *str,char c1,char c2);

int main(void) {
    char test[] = "aabbcc";
    int a=0;
    
    printf("before:%s\ncount:%d\n",test,a);
    a=subst(test,'a','f');
    printf("after:%s\ncount:%d\n",test,a);
    
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

