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
#define endp NULL//strtol you pointer
#define base1 10//10sinnsuu

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
    char others[LIMIT];//備考
};

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
void cmd_print(struct profile *pro,int param);
void cmd_read(char *filename);
void cmd_write(char *filename);
void cmd_find(char *keyword);
void cmd_sort(int youso);
void exec_command(char cmd, char *param);

/*profile*/
struct profile *new_profile(struct profile *pro,char *str);

/*GLOBAL*/
struct profile profile_data_store[10000];
int profile_data_nitems = 0;

/*MAIN*/
int main(void){

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
       
        if(count>max)break;
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

    if(count<max)count = luck;
    else if(count>max)count = over;
    error_split(count);
    return count;
}

int get_line(char *input){
    printf("\n>>>>>");
    if (fgets(input, LIMIT + 1, stdin) == NULL){
        printf("error:NULL\n");
        return 0; /* 失敗EOF */
    }
    subst(input, '\n', '\0');
    return 1; /*成功*/
}

void error_split(int check){
    switch(check){
        case luck:
            printf("luck.");
            break;
        
        case over:
            printf("over.");
            break;
        
        default:
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
        new_profile(&profile_data_store[profile_data_nitems++],line);
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
            cmd_print(&profile_data_store[0],strtol(param,endp,base1));
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
void cmd_print(struct profile *pro,int param){
    if(profile_data_nitems == 0){
        printf("No record. No print.\n");
        return ;
    }
    fprintf(stderr, "******print record data******\n");
    int i;
    printf("param is %d.\n",param);
    
    if(param == 0){
        for(i=0;i<profile_data_nitems;i++){
            printf("data : %d-----------------------------------\n",i);
            fprintf(stderr,"id     :%d\n",(pro+i)->id);
            fprintf(stderr,"name   :%s\n",(pro+i)->name);
            fprintf(stderr,"date   :%d/%d/%d\n",(pro+i)->found.y,(pro+i)->found.m,(pro+i)->found.d);
            fprintf(stderr,"adress :%s\n",(pro+i)->add);
            fprintf(stderr,"memo   :%s\n",(pro+i)->others);
            fprintf(stderr,"--------------------------------------------\n");
        }
    }
    
    else if(param > 0){
        
        if( param > profile_data_nitems ){
            param = profile_data_nitems;
        }
                
        for(i = 0;i<param;i++){
            printf("data : %d-----------------------------------\n",i);
            fprintf(stderr,"id     :%d\n",(pro+i)->id);
            fprintf(stderr,"name   :%s\n",(pro+i)->name);
            fprintf(stderr,"date   :%d/%d/%d\n",(pro+i)->found.y,(pro+i)->found.m,(pro+i)->found.d);
            fprintf(stderr,"adress :%s\n",(pro+i)->add);
            fprintf(stderr,"memo   :%s\n",(pro+i)->others);
            fprintf(stderr,"--------------------------------------------\n");
        }
    }
    
    else if(param < 0){
        
        param *= -1;
        if( param > profile_data_nitems ){
            param = profile_data_nitems;
        }
        pro += profile_data_nitems;
                
        for(i ;i<param;i++){
            printf("data : %d-----------------------------------\n",i);
            fprintf(stderr,"id     :%d\n",(pro+i)->id);
            fprintf(stderr,"name   :%s\n",(pro+i)->name);
            fprintf(stderr,"date   :%d/%d/%d\n",(pro+i)->found.y,(pro+i)->found.m,(pro+i)->found.d);
            fprintf(stderr,"adress :%s\n",(pro+i)->add);
            fprintf(stderr,"memo   :%s\n",(pro+i)->others);
            fprintf(stderr,"--------------------------------------------\n");
        }
        if(i==0){
            printf("no data.\n-----------------------------\n");
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
struct profile *new_profile(struct profile *pro,char *str){
    char *ret1[maxsplit],*ret2[maxsplit-2];

    printf("data_nitems:%d\n",profile_data_nitems);
    
    if(split(str,ret1,',',maxsplit)!=maxsplit){
        printf("Error:wrong format of input(ex.001,name,1999-01-01,address,other)\n");
        return NULL;
    }//文字列用
    
    pro->id = strtol(ret1[0],endp,base1);
    if( pro->id == 0){
        printf("Error:ID is NUMBER.\n");
        return NULL;
    }

    strncpy(pro->name, ret1[1],70);//
    strncpy(pro->add, ret1[3],70);//
    strncpy(pro->others, ret1[4],LIMIT);//

    if(split(ret1[2],ret2,'-',maxsplit-2)!=maxsplit-2){
        printf("Error:wrong format of date.(ex.1999-01-01)\n");
        return NULL;
    }//設立日
    pro->found.y = strtol(ret2[0],endp,base1);
    pro->found.m = strtol(ret2[1],endp,base1);
    pro->found.d = strtol(ret2[2],endp,base1);
    
    printf("Add profile.\n");
    return pro;
}
