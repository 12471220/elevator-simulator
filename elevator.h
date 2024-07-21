#ifndef ELEVATOR_H
#define ELEVATOR_H

#define MAX_FLOOR 12

// a certain layer
struct floor{
    int fswitch; //-1, 0, 1
    int layer;
};

//the hole elevator
struct elevator{
    struct floor *f;
    int buttons[MAX_FLOOR];
    int currentf;
    int targetf;
    int direction; //-1,0,1
};

void init(struct elevator* e);
void use_floor_switch(struct elevator* e,int layer,int direction);
void use_elevator_button(struct elevator* e,int layer);
void run(struct elevator* e);
void change_target(struct elevator *e); //find the end floor of current direction.
void open_door_judgement(struct elevator *e); //judge whether open door. if it can, then open.
void detail_info(struct elevator* e);

#endif