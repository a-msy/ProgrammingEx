#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bb = 500;
int rr(){

    int balance = bb;
    int bet = 1;
    int ro = 0;
    double zero_count = 0;
    int min_balance=bb;
    int max_balance=bb;
    int hit = 0;
    int game_second=0;
    double per=0;
    int i;
    int ret=0;

    for(i=1;i<=1000;i++){

        //printf("%d kaime---------\n",i);

        if( i%38 == 0){
            bet *= 2;
        }
        //printf("bet:%d\n",bet);
        ro = rand()%37;
        game_second+=30;
        //printf("ro:%d\n",ro);
        if(ro == 0){
            zero_count++;
            balance += (bet*36);
            bet=1;
        }
        else{
            balance -= bet;
        }

        if(balance>max_balance){
            max_balance=balance;
        }
        
        if(balance<min_balance){
            min_balance=balance;
        }
        //printf("balance:%d\n",balance);
        //printf("-----------------\n");
        if(balance >= bb*1.1){
            ret=0;
            break;
        }

        if(balance < bb*0.5){
            ret=1;
            break;
        }

    }
    per=(zero_count/i)*100;
    //printf("zerocount:%.lf\n",zero_count);
    //printf("per:%.5lf%%\n",per);
    //printf("min_balance:%d\n",min_balance);
    //printf("max_balance:%d\n",max_balance);
    //printf("total_game_time:%d\n",game_second/60);
    return ret;
}

int nissu = 5;
int main(void){
    srand((unsigned int)time(NULL));
    int hai[nissu];
    int a=0;
    double syuusi=0;
    double b=0,c=0;

    for(a=0;a<nissu;a++){
        hai[a]=rr();
        printf("%d ",hai[a]);
        if(hai[a]==0){
            syuusi+=bb*0.1;
            c++;
        }
        else syuusi-=(bb*0.5);
    }

    printf("\nwin%%:%lf\n",c/nissu*100);
    printf("syuusi:%lf\n",syuusi);

    return 0;
}
