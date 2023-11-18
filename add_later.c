/* DESTINATION IS WRONG
// FOXES - TRACKING (FUNCTION)
int tracking(char scenery[LINES][COLUMNS], int position[2], RABBIT** rabbits){
    RABBIT* rabbit = *rabbits;
    if(rabbit == NULL){
        return 0, 0, 0;
    }
    int min, distance, destination[2];
    min = abs(rabbit->position[0] - position[0]) + abs(rabbit->position[1] - position[1]);

    while(rabbit != NULL){
        distance = abs(rabbit->position[0] - position[0]) + abs(rabbit->position[1] - position[1]);     // Manhattan distance |x2 - x1| + |y2 - y1|
        if(distance < min){
            destination[0] = rabbit->position[0];
            destination[1] = rabbit->position[1];
            min = distance;
        }
        rabbit = rabbit->next;
    }
    return 1, destination[0], destination[1];
}
*/




// TRYING TO TRACK THE RABBITS (NOT WORKING)
// ADD AFTER FOX TRY TO HUNT AND DONT MAKE IT (INSIDE FOX MOVE FUNCTION)
/*
    if(!empty){
        int found = 0, destination[2];
        found, destination[0], destination[1] = tracking(scenery, fox->position, rabbits);
        printf("DESTINATION: (%d, %d)\n", destination[0], destination[1]);
        if(found){  // FIND THE NEAREST
            if(destination[0] < x && scenery[x-1][y] == EMPTY_SYMBOL){  // UP
                axis[0] = 0;
                empty++;
            }
            if(destination[1] > y && scenery[x][y+1] == EMPTY_SYMBOL){  // RIGHT
                if(empty == 1){
                    axis[1] = 1;
                }else{
                    axis[1] = 0;
                }
                empty++;
            }
            if(destination[0] > x && scenery[x+1][y] == EMPTY_SYMBOL){  // DOWN
                if(empty == 1){
                    axis[2] = 1;
                }else{
                    axis[2] = 0;
                }
                empty++;
            }
            if(destination[1] < y && scenery[x][y-1] == EMPTY_SYMBOL){  // LEFT
                if(empty == 1){
                    axis[3] = 1;
                }else{
                    axis[3] = 0;
                }
                empty++;
            }
            printf("AXIS: (%d, %d, %d, %d)\n", axis[0], axis[1], axis[2], axis[3]);
        }
    }
*/