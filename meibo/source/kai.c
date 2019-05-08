#include<stdio.h>    
#include<stdlib.h>
#include<string.h>

struct date{//生年月日の構造体を宣言
  int y;
  int m;
  int d;
};

struct profile {//名簿のデータの構造体を宣言
  int id;//int型でIDを読み込む 
  char name[70];//名前を70バイト分読み込む
  struct date birthday;//L.5で宣言した構造体を読み込む
  char adress[70];//住所を70バイト分読み込む
  char memo[512];//備考を512バイト分読み込む
}data[10000];//上記の構造体を10000確保する

int nprofile =0;//nprofileをグローバル変数とする


void subst(char *str){//subst関数を宣言
  while(*str != '\0'){
    if(*str == '\n'){
      *str = '\0';
    }
    str++;
  }
}
//文字列内の改行（\n）をナル文字に変える


void split(char *line,char *point[],int n,char c){//split関数を宣言
  int i;
  point[0]=line;//str[0]の先頭アドレスを格納
  for(i=1;i<n;i++){
    while(*line != c)line++;
    *line='\0';//「,」のときナル文字に変換
    line++;
    point[i]=line;//「,」の次の文字を読み込む
  }
}

void csv(char *str){
  char *ret[5],*ret2[3];
  int i;
  subst(str);
  split(str,ret,5,',');//文字列用split
  
  data[nprofile].id=atoi(ret[0]);
  strcpy(data[nprofile].name   ,ret[1]);
  strcpy(data[nprofile].adress ,ret[3]);
  strcpy(data[nprofile].memo   ,ret[4]);
  
  split(ret[2],ret2,3,'-');//生年月日用split
 
  data[nprofile].birthday.y=atoi(ret2[0]);
  data[nprofile].birthday.m=atoi(ret2[1]);
  data[nprofile].birthday.d=atoi(ret2[2]);
  
  nprofile++;//次の構造体に移動  
}

void cmdQ(){
  printf("コマンドQを実行\n");
  printf("---------------------\n");
  printf("プログラム終了\n");
  exit(0);
}

void cmdC(){
  printf("コマンドCを実行\n");
  printf("---------------------\n");
  printf("データ数 %d\n",nprofile);//グローバル変数の数を読み込み
  printf("プログラム終了\n");  
}

void cmdP(char *str){
  int i;
  if (atoi(str+3) ==0){//n=0の場合
    for(i=0;i<nprofile;i++){
      printf("id     :%d\n",data[i].id);
      printf("name   :%s\n",data[i].name);
      printf("date   :%d/%d/%d\n",data[i].birthday.y,data[i].birthday.m,data[i].birthday.d);
      printf("adress :%s\n",data[i].adress);
      printf("memo   :%s\n",data[i].memo);
      printf("\n");
    }
  }else if(atoi(str+3) < 0){//nが負の場合
    for(i=nprofile+atoi(str+3);i<nprofile;i++){
      printf("id     :%d\n",data[i].id);
      printf("name   :%s\n",data[i].name);
      printf("date   :%d/%d/%d\n",data[i].birthday.y,data[i].birthday.m,data[i].birthday.d);
      printf("adress :%s\n",data[i].adress);
      printf("memo   :%s\n",data[i].memo);
      printf("\n");
    }
  }else if(atoi(str+3) > 0){//nが正の場合
    for(i=0;i<atoi(str+3);i++){
      printf("id     :%d\n",data[i].id);
      printf("name   :%s\n",data[i].name);
      printf("date   :%d/%d/%d\n",data[i].birthday.y,data[i].birthday.m,data[i].birthday.d);
      printf("adress :%s\n",data[i].adress);
      printf("memo   :%s\n",data[i].memo);
      printf("\n"); 
    } 
  }
}

void cmdR(char *str){
  FILE *fp;//ファイルポインタの宣言
  char line[1024];//メモリの確保

  str=str+3;//読み込むポインタを指定

  if((fp = fopen(str,"r")) == NULL){//
    printf("読み込み失敗\n");
    return;
  }
  while(fgets(line,1024,fp) != NULL){
    csv(line);//csv関数処理
  }
  fclose(fp);
  printf("読み込み完了\n");
}

void cmdW(char *str){
  FILE *fp;//ファイルポインタの宣言
  int i;
  str=str+3;//書き込むポインタを指定

  if((fp = fopen(str,"w")) == NULL){
    printf("読み込み失敗\n");
    return;
  }
  for(i=0;i<nprofile;i++){
    fprintf(fp,"%d,%s,%d-%d-%d,%s,%s\n",data[i].id,
	                                data[i].name,
	                                data[i].birthday.y,
	                                data[i].birthday.m,
	                                data[i].birthday.d,
	                                data[i].adress,
	                                data[i].memo);
  }
      
  fclose(fp);

}

void cmdF(char *str){

  int i;
  int n=0;

  str=str+3;

  for(i=0;i<nprofile;i++){
    if(data[i].id == atoi(str) ||
       strstr(data[i].name,str) != NULL ||
       strstr(data[i].adress,str) != NULL ||
       data[i].birthday.y == atoi(str) ){
      printf("id     :%d\n",data[i].id);
      printf("name   :%s\n",data[i].name);
      printf("date   :%d/%d/%d\n",data[i].birthday.y,data[i].birthday.m,data[i].birthday.d);
      printf("adress :%s\n",data[i].adress);
      printf("memo   :%s\n",data[i].memo);   
      printf("\n");
      n=1;
    }
  }
  if(n == 0){
    printf("一致するものがありません\n");
  }
}

int cmp_id(struct profile *p1,struct profile *p2){
  return p1->id - p2->id;
}

int cmp_name(struct profile *p1,struct profile *p2){
 return strcmp(p1->name,p2->name);
}

int cmp_birthday(struct profile *p1,struct profile *p2){

  int t1 = p1->birthday.y*10000+p1->birthday.m*100+p1->birthday.d;
  int t2 = p2->birthday.y*10000+p2->birthday.m*100+p2->birthday.d;

  return t1 - t2;
}

int cmp_adress(struct profile *p1,struct profile *p2){
  return strcmp(p1->adress,p2->adress);
}

void cmdS(int n){

  int i,j;

  struct profile temp;

  int (*cmp)(struct profile *p1,struct profile *p2);

  if(n==1){
    cmp=cmp_id;
  }else if(n==2){
    cmp=cmp_name;
  }else if(n==3){
    cmp=cmp_birthday;
  }else if(n==4){
    cmp=cmp_adress;
  }

  for(i=0;i<nprofile-1;i++){
    for(j=nprofile-1;j>i;j--){
      if((*cmp)(&data[j-1],&data[j])  > 0){
	temp=data[j];
	data[j]=data[j-1];
	data[j-1]=temp;
      }
    }
  }
  printf("sort ok\n");
}

void cmd(char *str){
  if(*(str+1) =='Q' || *(str+1)=='q'){//コマンドQ
    cmdQ();      
  }else if(*(str+1) =='C' || *(str+1)=='c'){//コマンドC
    cmdC();
  }else if(*(str+1) =='P' || *(str+1)=='p'){//コマンドP
    cmdP(str);
  }else if(*(str+1) =='R' || *(str+1)=='r'){//コマンドR
    subst(str);
    cmdR(str);
  }else if(*(str+1) =='W' || *(str+1)=='w'){//コマンドW
    subst(str);
    cmdW(str);
  }else if(*(str+1) =='F' || *(str+1)=='f'){//コマンドF
    subst(str);
    cmdF(str);
  }else if(*(str+1) =='S' || *(str+1)=='s'){//コマンドS
    subst(str);
    cmdS(atoi(str+3));
  }
}
  main(){
  char str[256];

  while(1){//繰り返し文を使いコマンドを繰り返す
    
    printf("コマンド，もしくはデータを入力してください\n");
    
    fgets(str,sizeof(str),stdin);//fgetsで文字列を読み込む
    if(*str != '%'){
      csv(str);
    }
    cmd(str);
  } 
}
