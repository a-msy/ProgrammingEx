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
#define maxsplit 5//最大分割数
#define luck -1
#define over -2
#define endp NULL//strtol 用ポインタ
#define base1 10//10進数

typedef enum{
    null,//
    LUCK,
    OVER,//
    NOTDEFINED,//
    NORECORD,//
    OVERNUMBERRECORD,//
    FORMATINPUT,
    FORMATID,
    FORMATDATE,//
    NUMITEM,//
    ERRORNUM,//
    NOFILEOPEN,
    OVERNITEMS//

} ERROR;

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
    char *others;//備考
};

/*subst*/
int subst(char *str,char c1,char c2);

/*split*/
int split(char *str,char *ret[],char sep,int max);
void error_split(int check);

/*get_line*/
int get_line(char *input);
int get_line_fp(FILE *fp,char *input);

/*parse_line*/
void parse_line(char *line);

void printdata(struct profile *pro, int i);
/*cmd*/
void cmd_quit();
void cmd_check();
void cmd_print(struct profile *pro,int param);
void cmd_read(char *filename);
void cmd_write(char *filename);
void cmd_find(char *keyword);
void swap_struct(struct profile *i, struct profile *j);
int compare_profile(struct profile *p1, struct profile *p2, int column);
int compare_date(struct date *d1, struct date *d2);
void cmd_sort(int youso);
void cmd_delete(int param);
void exec_command(char cmd, char *param);

/*profile*/
struct profile *new_profile(struct profile *pro,char *str);
char *date_to_string(char buf[],struct date *date);

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
    return get_line_fp(stdin,input);
}

int get_line_fp(FILE *fp,char*input){
    fprintf(stderr,"\n>>>>>");
    
    if (fgets(input, LIMIT + 1, fp) == NULL){
        fprintf(stderr,"ERROR %d:NULL--getline()\n",null);
        return 0; /* 失敗EOF */
    }
    subst(input, '\n', '\0');
    
    return 1; /*成功*/
}

void error_split(int check){
    switch(check){
        case luck:
            fprintf(stderr,"ERROR %d:luck--split()\n",LUCK);
            break;
        
        case over:
            fprintf(stderr,"ERROR %d:over--split()\n",OVER);
            break;
        
        default:
            break;
    }
    return;
}

void parse_line(char *line){
    if(line[0]=='%'){
        exec_command(line[1], &line[3]);
    }
    else{
        new_profile(&profile_data_store[profile_data_nitems],line);
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

        case 'D':
            break;
        
        case 'S':
            cmd_sort(strtol(param,endp,base1));
        break;

        
        default:
            fprintf(stderr, "ERROR %d:%%%c command is not defined.--exec_command()\n",NOTDEFINED,cmd);
        break;
    }
 }

void cmd_quit(){
    fprintf(stderr, "END SYSTEM.\n");
    exit(0);
    return;
}
void cmd_check(){
    fprintf(stdout,"%d profile(s)\n",profile_data_nitems);
    return;
}
void cmd_print(struct profile *pro,int param){
    if(profile_data_nitems == 0){
        fprintf(stderr,"ERROR %d:No record. No print.--cmd_print()\n",NORECORD);
        return ;
    }
    int i;
    fprintf(stderr,"param is %d.\n",param);
    
    if(param == 0){//０のとき
    fprintf(stderr, "******print record data******\n");
        for(i=0;i<profile_data_nitems;i++){
            printdata(pro+i,i);
        }
    }
    
    else if(param > 0){//正のとき
        
        if( param > profile_data_nitems ){
            fprintf(stderr,"ERROR %d:over number of record.--cmd_print()\n",OVERNUMBERRECORD);
            fprintf(stderr,"ERROR %d:number of item is %d\n",NUMITEM,profile_data_nitems);
            return;
        }
        fprintf(stderr, "******print record data******\n");
        for(i = 0;i<param;i++){
            printdata(pro+i,i);
        }
    }
    
    else if(param < 0){//負の時
        
        param *= -1;
        if( param > profile_data_nitems ){
            fprintf(stderr,"ERROR %d:over number of record.--cmd_print()\n",OVERNUMBERRECORD);
            fprintf(stderr,"ERROR %d:number of item is %d\n",NUMITEM,profile_data_nitems);
            return;
        }
        pro += profile_data_nitems-param;
        fprintf(stderr, "******print record data******\n");
        for(i=0 ;i<param;i++){
            printdata(pro+i,profile_data_nitems-param+i);
        }
    }
    return;
}

void printdata(struct profile *pro, int i){
    fprintf(stderr,"data  : %5d ------------------------------\n",i+1);
    fprintf(stdout,"Id    : %d\n",pro->id);
    fprintf(stdout,"Name  : %s\n",pro->name);
    fprintf(stdout,"Birth : %04d-%02d-%02d\n",pro->found.y,pro->found.m,pro->found.d);
    fprintf(stdout,"Addr  : %s\n",pro->add);
    fprintf(stdout,"Com.  : %s\n\n",pro->others);
    fprintf(stderr,"--------------------------------------------\n");
}

void cmd_read(char *filename){
    char line[LIMIT+1];
    FILE *fp;
    
    if((fp = fopen(filename,"r"))==NULL){
        fprintf(stderr,"ERROR %d:openfile error!!!---cmd_read()\n",NOFILEOPEN);
        return;
    }
    while(get_line_fp(fp,line)){
        parse_line(line);
    }
    fclose(fp);
    return;
}

void cmd_write(char *filename){
    FILE *fp;
    int i;
    if((fp = fopen(filename,"w"))==NULL){
        fprintf(stderr,"ERROR %d:openfile error!!!---cmd_write()\n",NOFILEOPEN);
        return;
    }
    for(i=0;i < profile_data_nitems;i++){
        fprintf(fp,"%d,",profile_data_store[i].id);
        fprintf(fp,"%s,",profile_data_store[i].name);
        fprintf(fp,"%d-%d-%d,",profile_data_store[i].found.y,profile_data_store[i].found.m,profile_data_store[i].found.d);
        fprintf(fp,"%s,",profile_data_store[i].add);
        fprintf(fp,"%s",profile_data_store[i].others);
        fprintf(fp,"\n");
    }
    fclose(fp);
    fprintf(stderr,"wrote %s\n",filename);
    return;
}

char *date_to_string(char buf[],struct date *date){
    sprintf(buf,"%04d-%02d-%02d",date->y,date->m,date->d);
    return buf;
}
void cmd_find(char *keyword){
    int i,check=0;
    struct profile *p;
    char found_str[11];
    
    for(i=0;i < profile_data_nitems;i++){
        p=&profile_data_store[i];
        date_to_string(found_str,&p->found);
        if( 
                (p->id) == strtol(keyword,endp,base1)||
                strcmp(p->name,keyword)==0||
                strcmp(p->add,keyword)==0||
                strcmp(p->others,keyword)==0||
                strcmp(found_str,keyword)==0
            ){
                printdata(p,i);
                check=1;
        }
    }
    
    if(check==0){
        fprintf(stderr,"No match data.\n");
    }
    
    return;
}
void swap_struct(struct profile *i, struct profile *j){
    struct profile temp;
    
    temp = *j;
    *j = *i;
    *i = temp;
    
    return;
}

int compare_profile(struct profile *p1, struct profile *p2, int youso)
{
    if(youso < 0)youso*=-1;
  switch (youso) {
    case 1:
      return (p1->id) - (p2->id);
    case 2:
      return strcmp(p1->name,p2->name); /* name */
    case 3:
      return compare_date(&p1->found,&p2->found); /*found*/
    case 4:
      return strcmp(p1->add, p2->add); /* home */
    case 5:
      return strcmp(p1->others, p2->others); /* comment */
    }
}

int compare_date(struct date *d1, struct date *d2)
{
  if (d1->y != d2->y) return d1->y - d2->y;
  if (d1->m != d2->m) return d1->m - d2->m;
  return (d1->d) - (d2->d);
}

void cmd_sort(int youso){
    /*youso>0 syoujyunn, youso<0 koujyunn*/
    int i,j,check=0;
    
    for(i=0;i<profile_data_nitems;i++){
        for(j=0;j<profile_data_nitems-1;j++){
            if(compare_profile(&profile_data_store[j],&profile_data_store[j+1],youso) > 0){
                swap_struct(&profile_data_store[j],&profile_data_store[j+1]);
                check++;
            }
        }
    }
    printf("%d swap.\n",check);
    return;/*sort kurousitane*/
}

struct profile *new_profile(struct profile *pro,char *str){
    char *ret1[maxsplit],*ret2[maxsplit-2];
    if(profile_data_nitems>10000){
        fprintf(stderr,"ERROR %d:Can't add record--new_profile()\n",OVERNITEMS);
        return NULL;
    }
    if(split(str,ret1,',',maxsplit)!=maxsplit){
        fprintf(stderr,"ERROR %d:wrong format of input(ex.001,name,1999-01-01,address,other)--new_profile()\n",FORMATINPUT);
        return NULL;
    }//文字列用

    pro->id = strtol(ret1[0],endp,base1);
    if( pro->id == 0){
        fprintf(stderr,"ERROR %d:ID is NUMBER.--new_profile()\n",FORMATID);
        return NULL;
    }

    strncpy(pro->name, ret1[1],70);//名前のコピー
    strncpy(pro->add, ret1[3],70);//住所
    pro->others = (char *)malloc(sizeof(char)*(strlen(ret1[4])+1));
    strcpy(pro->others, ret1[4]);//備考,MAX 1024bytes

    if(split(ret1[2],ret2,'-',maxsplit-2)!=maxsplit-2){
        fprintf(stderr,"ERROR %d:wrong format of date.(ex.1999-01-01)--new_profile()\n",FORMATDATE);
        return NULL;
    }//設立日
    pro->found.y = strtol(ret2[0],endp,base1);
    pro->found.m = strtol(ret2[1],endp,base1);
    pro->found.d = strtol(ret2[2],endp,base1);
    
    fprintf(stderr,"Add profile.\n");
    profile_data_nitems++;
    return pro;
}
