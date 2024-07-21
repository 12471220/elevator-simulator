#include"elevator.h"
#include<malloc.h>
#include<stdio.h>
#include<unistd.h>

void init(struct elevator* e){
    int i;
    e->f=(struct floor*)malloc(sizeof(struct floor)*MAX_FLOOR);
    for(i=0;i<MAX_FLOOR;i++){
        e->f[i].fswitch=0;
        e->f[i].layer=i+1;
        e->buttons[i]=0;
    }
    e->direction=0;
    e->currentf=0;
    e->targetf=0;
}

void run(struct elevator* e){
    for(;;){
        detail_info(e);
        open_door_judgement(e);
        change_target(e);
        e->currentf+=e->direction;
        sleep(1);
    }

}

void use_floor_switch(struct elevator* e,int layer,int direction){
    // the layer is fit by array's index ,FROM 0 TO MAX_FLOOR-1
    if(layer>=0&&layer<=MAX_FLOOR-1&&(direction==1||direction==-1)){
        // if the demand is on the way and bigger than target, change the target.
        if(e->direction==0){
            e->direction=layer>e->currentf?1:-1;
            e->targetf=layer;
        }
        if((layer>e->targetf && e->direction==1) || (layer<e->targetf && e->direction==-1)){
            e->targetf=layer;
        } 
        e->f[layer].fswitch=direction;
    }
    else{
        printf("error: illegal input.\n");
    }

}

void use_elevator_button(struct elevator* e,int layer){
    //check out
    if(layer>=0&&layer<=MAX_FLOOR-1){
        //if you press twice, the signal will be removed.
        e->buttons[layer]=!e->buttons[layer];
    }
    else{
        printf("error: illegal input.\n");
    }
}

void change_target(struct elevator* e){
    int i;
    if(!e->direction){
        //both two kind of button is 0 ,the elevator will be go up.
        for(i=0; i<MAX_FLOOR&&(!e->f[i].fswitch&&!e->buttons[i]) ;i++); 
        if(i!=MAX_FLOOR){
            if(e->currentf<i){
                e->direction=1;
                e->targetf=i;
            }
            else if(e->currentf>i){
                e->direction=-1;
                e->targetf=i;
            }
        }
    }
    if(e->direction==-1){
        //down
        for(i=0;!e->f[i].fswitch&&!e->buttons[i];i++);
        if(i!=e->currentf)
            e->targetf=i;
    }else{
        //up
        for(i=MAX_FLOOR-1;!e->f[i].fswitch&&!e->buttons[i];i--);
        if(i!=e->currentf)
            e->targetf=i;
    }
}

void open_door_judgement(struct elevator* e){
    /**
     * when will we open the door?
     * 1. elevator's direction==layer's direction
     * 2. the layer is a target(inner button)
     * 3. the layer is the way end.
     */
    int flag=0;
    if(e->f[e->currentf].fswitch && e->f[e->currentf].fswitch==e->direction){
        flag=1;
        e->f[e->currentf].fswitch=0;
    }
    if(e->buttons[e->currentf]==1){
        flag=1;
        e->buttons[e->currentf]=0;
    }
    if(e->currentf==e->targetf && e->direction){
        flag=1;
        e->direction=0;
        e->f[e->currentf].fswitch=0;
    }

    if(flag){
        printf("%dF door is open!\n",e->currentf+1);
        sleep(3);
        printf("%dF door is closed!\n",e->currentf+1);
    }
    
}

void detail_info(struct elevator* e){
    if(!e->direction){
        printf("The elevator has stopped.\n");
    }
    else{
        printf("current:%dF, target:%dF ",e->currentf+1,e->targetf+1);
        if(e->direction==-1){
            printf("️⬇\n");
        }
        else if(e->direction==1){
            printf("⬆\n");
        }
    }
    
}