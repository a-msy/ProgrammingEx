/* 
 * File:   meibo.c
 * Author: 09430509
 *
 * Created on 2019/04/10
 * update on 2019/05/08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1024
#define maxsplit 5//5 ko ijyou wakeruto segmentation fault ni naru.
#define luck -1
#define over -2
#define endp NULL
#define base1 10

/*subst*/
int subst(char *str,char c1,char c2);

/*split*/
int split(char *str,char *ret[],char sep,int max);
void testprint_split(char *str,char sep);
void error_split(int check);

/*get_line*/
int get_line(char *input);
void testprint_get_line();

/*parse_line*/
void parse_line(char *line);

/*cmd*/
void cmd_quit();
void cmd_check();
void cmd_print(int param);
void cmd_read(char *filename);
void cmd_write(char *filename);
void cmd_find(char *keyword);
void cmd_sort(int youso);
void exec_command(char cmd, char *param);

/*profile*/
void new_profile(char *str);

struct date {
    int y;//year
    int m;//month
    int d;//day
};

struct profile{
    int id;//id
    char name[70];//schoolname
    struct date found;
    char add[70];//address
    char others[512];//備考
};


/*GLOBAL*/
struct profile profile_data_store[10000];
int profile_data_nitems = 0;

/*MAIN*/
int main(void){
    /*test
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
     */

    char line[LIMIT + 1];
    while (get_line(line)) {
        parse_line(line);
    }
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

    //if(count<max)count = luck;
    //else if(count>max)count = over;

    error_split(count);
    return count;
}

void error_split(int check){
    switch(check){
        case luck:
            printf("luck.\n");
            break;
        
        case over:
            printf("over.\n");
            break;
        
        default:
            printf("No Problem.\n");
            break;
    }
    return;
}

void testprint_split(char *str,char sep){
    int count;
    char *ret[maxsplit];
    printf("test %s\n",str);
    
    count=split(str,ret,sep,maxsplit);
    
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

    printf("please input line:");
    
    while (get_line(input)) {
        printf("*****test %d*****\n", ++n);
        testprint_split(input,',');
        printf("input line:");
    }
    return;
}

void parse_line(char *line){
    if(line[0]=='%'){
        exec_command(line[1], &line[3]);
    }
    else{
        new_profile(line);
    }
}

void exec_command(char cmd, char *param)
 {
    switch(cmd){
        case 'Q':
            cmd_quit();
        break;
        
        case 'C':
            cmd_check();
        break;
        
        case 'P':
            cmd_print(strtol(param,endp,base1));
        break;
        
        case 'R':
            cmd_read(param);
        break;
        
        case 'W':
            cmd_write(param);
        break;
        
        case 'F':
            cmd_find(param);
        break;
        
        case 'S':
            cmd_sort(strtol(param,endp,base1));
        break;

        
        default:
            fprintf(stderr, "%%%c command is not defined.\n",cmd);
        break;
    }
 }

void cmd_quit(){
    fprintf(stderr, "END SYSTEM.\n");
    exit(0);
    return;
}
void cmd_check(){
    fprintf(stderr, "check record num is ");
    fprintf(stderr,"%d\n",profile_data_nitems);
    return;
}
void cmd_print(int param){
    fprintf(stderr, "******print record data******\n");
    int i=0;
    if(param == 0){
        for(i=0;i<profile_data_nitems;i++){
            printf("data : %d-----------------------------------\n",i+1);
            fprintf(stderr,"id     :%d\n",profile_data_store[i].id);
            fprintf(stderr,"name   :%s\n",profile_data_store[i].name);
            fprintf(stderr,"date   :%d/%d/%d\n",profile_data_store[i].found.y,profile_data_store[i].found.m,profile_data_store[i].found.d);
            fprintf(stderr,"adress :%s\n",profile_data_store[i].add);
            fprintf(stderr,"memo   :%s\n",profile_data_store[i].others);
            fprintf(stderr,"--------------------------------------------\n");
        }
    }
    return;
}
void cmd_read(char *filename){
    fprintf(stderr, "read-%s.\n",filename);
    return;
}
void cmd_write(char *filename){
    fprintf(stderr, "write-%s.\n",filename);
    return;
}
void cmd_find(char *keyword){
    fprintf(stderr, "find-%s.\n",keyword);
    return;
}
void cmd_sort(int youso){
    fprintf(stderr, "sort-%d.\n",youso);
    return;
}
void new_profile(char *str){
    char *ret1[maxsplit],*ret2[maxsplit-2];
    int subst1,ret1sp,ret2sp,i=0;
    subst1 = subst(str,'\n','\0');

    printf("item_num:%d\n",profile_data_nitems+1);
    
    ret1sp = split(str,ret1,',',maxsplit);//文字列用
    profile_data_store[profile_data_nitems].id = strtol(ret1[0],endp,base1);
    strcpy(profile_data_store[profile_data_nitems].name, ret1[1]);
    strcpy(profile_data_store[profile_data_nitems].add, ret1[3]);
    strcpy(profile_data_store[profile_data_nitems].others, ret1[4]);

    ret2sp = split(ret1[2],ret2,'-',maxsplit-2);//設立日
    profile_data_store[profile_data_nitems].found.y = strtol(ret2[0],endp,base1);
    profile_data_store[profile_data_nitems].found.m = strtol(ret2[1],endp,base1);
    profile_data_store[profile_data_nitems].found.d = strtol(ret2[2],endp,base1);
    profile_data_nitems++;
}
