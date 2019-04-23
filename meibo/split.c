
#include <stdio.h>

int split(char *str,char *ret[],char sep,int max);
void testprint(char *str,char *ret[],char sep,int max);
void error_split(int check);

int main(void){
    int max = 5;
    char test1[] = "";//分割したい文字列
    char test2[] = ",,,";
    char test3[] = ",oka,yama";
    char test4[] = "ok,a,ya,,ma,a";
    char *ret[max];//分割後に入れる文字配列個数
    
    testprint(test1,ret,',',max);
    testprint(test2,ret,',',max);
    testprint(test3,ret,',',max);
    testprint(test4,ret,',',max);
    
    return 0;
}

void testprint(char *str,char *ret[],char sep,int max){
    int count;
    
    printf("test %s\n",str);
    
    count=split(str,ret,',',max);
    
    if(count <0 ) {
        error_split(count);
        return ;
    }
    
    for(int i = 0; i < count; i++){;
        printf("%d:%s\n",i+1, ret[i]);
    }
    
    printf("count is %d.\n\n",count);
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
    if(count>max)  count = -2;
    
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
}
