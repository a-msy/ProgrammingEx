
#include <stdio.h>

#define true 1
#define false 0

int split(char *str,char *ret[],char sep,int max);

int main(void){
    int max = 1024;
    char str[] = ",Iaaa,ma,,,sa,,ya";//分割したい文字列
    char *ret[100];//分割後に入れる文字配列
    int count;
    count=split(str,ret,',',max);
    for(int i = 0; i < count; i++){
        printf("%s\n", ret[i]);
    }
    return 0;
}

int split (char *str,char *ret[],char sep,int max){
    int count = 0;//分割数

    while (1){
        printf("%s split by %c start\n",str,sep);

        while(*str == sep){//区切り文字が連続であった場合
            printf("%c is split char.\n",*str);
            str++;
        }

        printf("%c is not  split char.1\n",*str);
        if(*str == '\0') {
            printf("string can not split.2\n");
            break;//からもじなら抜ける＝文字列はそのまま
        }

        ret[count++] = str;//strをいじればretもかわる
								printf("set ret is %s.\n",str);

        while( (*str != '\0') && (*str != sep) ){//区切り文字が見つかるまでポインタすすめる 
            printf("%c-6\n",*str);
            str++;
        }

        printf("%c is split char.3\n",*str); 
        if(*str == '\0') {
            printf("string can not split.4\n");
            break;//区切り文字がなかったら抜ける＝文字列はそのまま
        }

        *str = '\0';//ひとつとなりは必ず区切り文字のはずだからくぎる。
								str++;
								if(count>=max)break;
    }
    return count;
}