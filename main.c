#include"elevator.h"
#include<stdio.h>

void prepare(struct elevator* e){
    use_floor_switch(e,11,-1);
    use_floor_switch(e,7,-1);

    use_elevator_button(e,5);
}
int main(){
    struct elevator e;
    // printf("⬆️⬇️\n");
    
    init(&e);
    prepare(&e);
    run(&e);
}