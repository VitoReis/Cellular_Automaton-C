#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SCENERY
int LINES, COLUMNS, NUM_GENERATIONS, SCENERY_OBJECTS;
char EMPTY_SYMBOL = ' ', ROCKS_SYMBOL = '*';

// RABBITS
int RABBITS_POPULATION, RABBITS_BREEDING_TIME;
char RABBITS_SYMBOL = 'C';
typedef struct RABBIT{
    int age;
    int position[2];
    char symbol;
    struct RABBIT* next;
}RABBIT;

// FOXES
int FOXES_POPULATION, FOXES_BREEDING_TIME, FOXES_STARVATION_TIME;
char FOXES_SYMBOL = 'R';
typedef struct FOX{
    int age;
    int starvation;
    int position[2];
    char symbol;
    struct FOX* next;
}FOX;

// SPECIES BREEDING
int breeding_species(RABBIT** rabbits, RABBIT* rabbit, FOX** foxes, FOX* fox){
    if(rabbit != NULL){
        if(rabbit->age >= RABBITS_BREEDING_TIME){
            rabbit->age = 0;
            RABBIT* add = *rabbits;
            while(add->next != NULL){
                add = add->next;
            }
            RABBIT* new_rabbit = (RABBIT*)malloc(sizeof(RABBIT));
            new_rabbit->position[0] = rabbit->position[0];
            new_rabbit->position[1] = rabbit->position[1];
            new_rabbit->age = 0;
            new_rabbit->symbol = RABBITS_SYMBOL;
            new_rabbit->next = NULL;
            add->next = new_rabbit;
            return 1;
        }
    }else{
        if(fox->age >= FOXES_BREEDING_TIME){
            fox->age = 0;
            FOX* add = *foxes;
            while(add->next != NULL){
                add = add->next;
            }
            FOX* new_fox = (FOX*)malloc(sizeof(FOX));
            new_fox->position[0] = fox->position[0];
            new_fox->position[1] = fox->position[1];
            new_fox->age = 0;
            new_fox->symbol = FOXES_SYMBOL;
            new_fox->next = NULL;
            add->next = new_fox;
            return 1;
        }
    }
    return 0;
}


// RABBITS - MOVEMENT
char rabbits_movement(int num_gen, char scenery[LINES][COLUMNS], RABBIT** rabbits){
    int x, y, empty, axis[4], size = 1;
    RABBIT* rabbit = *rabbits;
    while(rabbit->next != NULL){
        rabbit = rabbit->next;
        size++;
    }
    rabbit = *rabbits;
    for(int i = 0; i < size; i++){
        x = rabbit->position[0];
        y = rabbit->position[1];
        int pos0[2] = {x-1, y}, pos1[2] = {x, y+1}, pos2[2] = {x+1, y}, pos3[2] = {x, y-1};
        
        // Movement priority
        axis[0] = -1;   // up
        axis[1] = -1;   // right
        axis[2] = -1;   // down
        axis[3] = -1;   // left
        empty = 0;

        if(x > 0 && scenery[x-1][y] == EMPTY_SYMBOL){   // UP
            axis[0] = 0;
            empty++;
        }
        if(y < COLUMNS-1 && scenery[x][y+1] == EMPTY_SYMBOL){   // RIGHT
            if(empty == 1){
                axis[1] = 1;
            }else{
                axis[1] = 0;
            }
            empty++;
        }
        if(x < LINES-1 && scenery[x+1][y] == EMPTY_SYMBOL){     // DOWN
            if(empty == 2){
                axis[2] = 2;
            }else if(empty == 1){
                axis[2] = 1;
            }else{
                axis[2] = 0;
            }
            empty++;
        }
        if(y > 0 && scenery[x][y-1] == EMPTY_SYMBOL){     // LEFT
            if(empty == 3){
                axis[3] = 3;
            }else if(empty == 2){
                axis[3] = 2;
            }else if(empty == 1){
                axis[3] = 1;
            }else{
                axis[3] = 0;
            }
            empty++;
        }
        
        if(empty > 0){
            int breeding = breeding_species(rabbits, rabbit, NULL, NULL);

            int cell = (x + y + num_gen) % empty;
            switch(cell){
                case 0:
                    if(axis[0] == 0){
                        rabbit->position[0] = pos0[0];
                        rabbit->position[1] = pos0[1];
                        scenery[pos0[0]][pos0[1]] = rabbit->symbol;
                    }else if(axis[1] == 0){                        
                        rabbit->position[0] = pos1[0];
                        rabbit->position[1] = pos1[1];
                        scenery[pos1[0]][pos1[1]] = rabbit->symbol;
                    }else if(axis[2] == 0){
                        rabbit->position[0] = pos2[0];
                        rabbit->position[1] = pos2[1];
                        scenery[pos2[0]][pos2[1]] = rabbit->symbol;
                    }else if(axis[3] == 0){
                        rabbit->position[0] = pos3[0];
                        rabbit->position[1] = pos3[1];
                        scenery[pos3[0]][pos3[1]] = rabbit->symbol;
                    }
                    if(!breeding){
                        scenery[x][y] = EMPTY_SYMBOL;
                        rabbit->age++;
                    }
                break;
                case 1:
                    if(axis[1] == 1){
                        rabbit->position[0] = pos1[0];
                        rabbit->position[1] = pos1[1];
                        scenery[pos1[0]][pos1[1]] = rabbit->symbol;
                    }else if(axis[2] == 1){
                        rabbit->position[0] = pos2[0];
                        rabbit->position[1] = pos2[1];
                        scenery[pos2[0]][pos2[1]] = rabbit->symbol;
                    }else if(axis[3] == 1){
                        rabbit->position[0] = pos3[0];
                        rabbit->position[1] = pos3[1];
                        scenery[pos3[0]][pos3[1]] = rabbit->symbol;
                    }
                    if(!breeding){
                        scenery[x][y] = EMPTY_SYMBOL;
                        rabbit->age++;
                    }
                break;
                case 2:
                    if(axis[2] == 2){
                        rabbit->position[0] = pos2[0];
                        rabbit->position[1] = pos2[1];
                        scenery[pos2[0]][pos2[1]] = rabbit->symbol;
                    }else if(axis[3] == 2){
                        rabbit->position[0] = pos3[0];
                        rabbit->position[1] = pos3[1];
                        scenery[pos3[0]][pos3[1]] = rabbit->symbol;
                    }
                    if(!breeding){
                        scenery[x][y] = EMPTY_SYMBOL;
                        rabbit->age++;
                    }
                break;
                case 3:
                    rabbit->position[0] = pos3[0];
                    rabbit->position[1] = pos3[1];
                    scenery[pos3[0]][pos3[1]] = rabbit->symbol;
                    if(!breeding){
                        scenery[x][y] = EMPTY_SYMBOL;
                        rabbit->age++;
                    }
                break;
            }
        }
        rabbit = rabbit->next;
    }
    return scenery[LINES][COLUMNS];
}

// FOXES - KILLING RABBITS
void kill_rabbit(char scenery[LINES][COLUMNS], RABBIT** rabbits, int position[2]){
    RABBIT* rabbit = *rabbits;
    RABBIT* aux = NULL;
    int found = 0;

    while(!found){
        if(rabbit->position[0] == position[0] && rabbit->position[1] == position[1]){
            if(aux == NULL){
                scenery[rabbit->position[0]][rabbit->position[1]] = EMPTY_SYMBOL;
                *rabbits = rabbit->next;
                free(rabbit);
                return;
            }else{
                scenery[rabbit->position[0]][rabbit->position[1]] = EMPTY_SYMBOL;
                aux->next = rabbit->next;
                free(rabbit);
                return;
            }
            
        }else{
            aux = rabbit;
            rabbit = rabbit->next;
        }
    }
}

/* DESTINATION IS WRONG
// FOXES - TRACKING
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

// FOXES - MOVEMENT/HUNTING
char foxes_movement(int num_gen, char scenery[LINES][COLUMNS], FOX** foxes, RABBIT** rabbits){
    int x, y, empty, axis[4], size = 1;
    FOX* fox = *foxes;
    
    while(fox != NULL){
        x = fox->position[0];
        y = fox->position[1];
        axis[0] = -1;
        axis[1] = -1;
        axis[2] = -1;
        axis[3] = -1;
        empty = 0;
        int pos0[2] = {x-1, y}, pos1[2] = {x, y+1}, pos2[2] = {x+1, y}, pos3[2] = {x, y-1};

        int hunt = 0;
        if(x > 0 && scenery[x-1][y] == RABBITS_SYMBOL){   // HUNT UP
            axis[0] = 0;
            empty++;
            hunt = 1;
        }
        if(y < COLUMNS-1 && scenery[x][y+1] == RABBITS_SYMBOL){   // HUNT RIGHT
            if(empty == 1){
                axis[1] = 1;
            }else{
                axis[1] = 0;
            }
            hunt = 1;
            empty++;
        }
        if(x < LINES-1 && scenery[x+1][y] == RABBITS_SYMBOL){     // HUNT DOWN
            if(empty == 2){
                axis[2] = 2;
            }else if(empty == 1){
                axis[2] = 1;
            }else{
                axis[2] = 0;
            }
            hunt = 1;
            empty++;
        }
        if(y > 0 && scenery[x][y-1] == RABBITS_SYMBOL){     // HUNT LEFT
            if(empty == 3){
                axis[3] = 3;
            }else if(empty == 2){
                axis[3] = 2;
            }else if(empty == 1){
                axis[3] = 1;
            }else{
                axis[3] = 0;
            }
            hunt = 1;
            empty++;
        }
        
        /*
        // TRYING TO TRACK THE RABBITS (NOT WORKING)
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

        // IF THERE ARE NO RABBITS (OR THE FOX IS STUCK SOMEWHERE [USED ​​IF TRACKING IS WORKING])
        if(!empty){
            if(x > 0 && scenery[x-1][y] == EMPTY_SYMBOL){   // UP
                axis[0] = 0;
                empty++;
            }
            if(y < COLUMNS-1 && scenery[x][y+1] == EMPTY_SYMBOL){   // RIGHT
                if(empty == 1){
                    axis[1] = 1;
                }else{
                    axis[1] = 0;
                }
                empty++;
            }
            if(x < LINES-1 && scenery[x+1][y] == EMPTY_SYMBOL){     // DOWN
                if(empty == 2){
                    axis[2] = 2;
                }else if(empty == 1){
                    axis[2] = 1;
                }else{
                    axis[2] = 0;
                }
                empty++;
            }
            if(y > 0 && scenery[x][y-1] == EMPTY_SYMBOL){     // LEFT
                if(empty == 3){
                    axis[3] = 3;
                }else if(empty == 2){
                    axis[3] = 2;
                }else if(empty == 1){
                    axis[3] = 1;
                }else{
                    axis[3] = 0;
                }
                empty++;
            }
        } 

        if(empty > 0){
            int breeding = breeding_species(NULL, NULL, foxes, fox);

            int cell = (x + y + num_gen) % empty;
            if(hunt){
                switch(cell){
                    case 0:
                        if(axis[0] == 0){
                            kill_rabbit(scenery, rabbits, pos0);
                            fox->starvation--;
                            fox->position[0] = pos0[0];
                            fox->position[1] = pos0[1];
                            scenery[pos0[0]][pos0[1]] = fox->symbol;
                        }else if(axis[1] == 0){
                            kill_rabbit(scenery, rabbits, pos1);
                            fox->starvation--;
                            fox->position[0] = pos1[0];
                            fox->position[1] = pos1[1];
                            scenery[pos1[0]][pos1[1]] = fox->symbol;
                        }else if(axis[2] == 0){
                            kill_rabbit(scenery, rabbits, pos2);
                            fox->starvation--;
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 0){
                            kill_rabbit(scenery, rabbits, pos3);
                            fox->starvation--;
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 1:
                        if(axis[1] == 1){
                            kill_rabbit(scenery, rabbits, pos1);
                            fox->starvation--;
                            fox->position[0] = pos1[0];
                            fox->position[1] = pos1[1];
                            scenery[pos1[0]][pos1[1]] = fox->symbol;
                        }else if(axis[2] == 1){
                            kill_rabbit(scenery, rabbits, pos2);
                            fox->starvation--;
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 1){
                            kill_rabbit(scenery, rabbits, pos3);
                            fox->starvation--;
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 2:
                        if(axis[2] == 2){
                            kill_rabbit(scenery, rabbits, pos2);
                            fox->starvation--;
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 2){
                            kill_rabbit(scenery, rabbits, pos3);
                            fox->starvation--;
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 3:
                        kill_rabbit(scenery, rabbits, pos3);
                        fox->starvation--;
                        fox->position[0] = pos3[0];
                        fox->position[1] = pos3[1];
                        scenery[pos3[0]][pos3[1]] = fox->symbol;
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                }
            }else{
                switch(cell){
                    case 0:
                        if(axis[0] == 0){
                            fox->position[0] = pos0[0];
                            fox->position[1] = pos0[1];
                            scenery[pos0[0]][pos0[1]] = fox->symbol;
                        }else if(axis[1] == 0){                        
                            fox->position[0] = pos1[0];
                            fox->position[1] = pos1[1];
                            scenery[pos1[0]][pos1[1]] = fox->symbol;
                        }else if(axis[2] == 0){
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 0){
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 1:
                        if(axis[1] == 1){
                            fox->position[0] = pos1[0];
                            fox->position[1] = pos1[1];
                            scenery[pos1[0]][pos1[1]] = fox->symbol;
                        }else if(axis[2] == 1){
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 1){
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 2:
                        if(axis[2] == 2){
                            fox->position[0] = pos2[0];
                            fox->position[1] = pos2[1];
                            scenery[pos2[0]][pos2[1]] = fox->symbol;
                        }else if(axis[3] == 2){
                            fox->position[0] = pos3[0];
                            fox->position[1] = pos3[1];
                            scenery[pos3[0]][pos3[1]] = fox->symbol;
                        }
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                    case 3:
                        fox->position[0] = pos3[0];
                        fox->position[1] = pos3[1];
                        scenery[pos3[0]][pos3[1]] = fox->symbol;
                        if(!breeding){
                            scenery[x][y] = EMPTY_SYMBOL;
                            fox->age++;
                        }
                    break;
                }
            }
        }
        fox = fox->next;
    }
    return scenery[LINES][COLUMNS];
}

// FOXES STARVATION
char foxes_starvation(char scenery[LINES][COLUMNS], FOX** foxes){
    FOX* fox = *foxes;
    FOX* aux = NULL;

    while(fox != NULL){
        if(fox->starvation >= FOXES_STARVATION_TIME){
            if(aux == NULL){
                scenery[fox->position[0]][fox->position[1]] = EMPTY_SYMBOL;
                *foxes = fox->next;
                free(fox);
                fox = *foxes;
            }else{
                scenery[fox->position[0]][fox->position[1]] = EMPTY_SYMBOL;
                aux->next = fox->next;
                free(fox);
                fox = aux->next;
            }
            
        }else{
            fox->starvation++;
            aux = fox;
            fox = fox->next;
        }
    }
}

// INSERTING ANIMAL IN THE SCENERY (FROM FILE)
char create_animal(char scenery[LINES][COLUMNS], RABBIT** rabbits, FOX** foxes, int position[2]){
    if(rabbits != NULL){
        RABBIT* new_rabbit = (RABBIT*)malloc(sizeof(RABBIT));
        if(scenery[position[0]][position[1]] == EMPTY_SYMBOL){
            new_rabbit->position[0] = position[0];
            new_rabbit->position[1] = position[1];
            new_rabbit->age = 0;
            new_rabbit->symbol = RABBITS_SYMBOL;
            new_rabbit->next = NULL;
            scenery[position[0]][position[1]] = new_rabbit->symbol;
            if(*rabbits == NULL){
                *rabbits = new_rabbit;
            }else{
                RABBIT* p = *rabbits;
                while(p->next != NULL){
                    p = p->next;
                }
                p->next = new_rabbit;
            }
        }else{
            printf("ERROR: Unable to position RABBIT at (%d, %d)", position[0], position[1]);
            exit(1);
        }
    }else{
        FOX* new_fox = (FOX*)malloc(sizeof(FOX));
        if(scenery[position[0]][position[1]] == EMPTY_SYMBOL){
            new_fox->age = 0;
            new_fox->starvation = 0;
            new_fox->position[0] = position[0];
            new_fox->position[1] = position[1];
            new_fox->symbol = FOXES_SYMBOL;
            new_fox->next = NULL;
            scenery[position[0]][position[1]] = new_fox->symbol;
            if(*foxes == NULL){
                *foxes = new_fox;
            }else{
                FOX* p = *foxes;
                while(p->next != NULL){
                    p = p->next;
                }
                p->next = new_fox;
            }
        }else{
            printf("ERROR: Unable to position FOX at (%d, %d)", position[0], position[1]);
            exit(1);
        }
    }
    return scenery[LINES][COLUMNS];
}

// CREATING SCENARIO FROM FILE
char creating_scenery(FILE* entry, char scenery[LINES][COLUMNS], RABBIT** rabbits, FOX** foxes){
    for(int i = 0; i < LINES; i++){
        for(int j = 0; j < COLUMNS; j++){
            scenery[i][j] = EMPTY_SYMBOL;
        }
    }

    char word[50];
    int position[2];
    while(fscanf(entry, "%s", word) == 1){
        if(strcmp(word, "RAPOSA") == 0){
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[0]);
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[1]);
            scenery[LINES][COLUMNS] = create_animal(scenery, NULL, foxes, position);
        }else if(strcmp(word, "COELHO") == 0){
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[0]);
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[1]);
            scenery[LINES][COLUMNS] = create_animal(scenery, rabbits, NULL, position);
        }else if(strcmp(word, "ROCHA") == 0){
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[0]);
            fscanf(entry, "%s", word);
            sscanf(word, "%d", &position[1]);
            scenery[position[0]][position[1]] = ROCKS_SYMBOL;
        }
    }
    return scenery[LINES][COLUMNS];
}

// PRINT THE SCENERY
void printS(char scenery[LINES][COLUMNS], int gen){
    FILE *exit;
    exit = fopen("exit.txt", "a");
    fprintf(exit, "GENERATION %d:\n", gen);
    // NUMBERING COLUMNS
    fprintf(exit, "  ");
    for(int i = 0; i < COLUMNS; i++){
        fprintf(exit, "%d", i);
    }
    fprintf(exit, "\n");

    // SCENERY ROOF
    fprintf(exit, "  ");
    for(int i = 0; i < COLUMNS; i++){
        fprintf(exit, "-", gen);
    }
    fprintf(exit, "\n");

    // SCENERY
    for(int i = 0; i < LINES; i++){
        fprintf(exit, "%d|", i);
        for(int j = 0; j < COLUMNS; j++){
            fprintf(exit, "%c", scenery[i][j]);
        }
       fprintf(exit, "|\n");
    }

    // SCENERY FLOOR
    fprintf(exit, "  ");
    for(int i = 0; i < COLUMNS; i++){
        fprintf(exit, "-", gen);
    }
    fprintf(exit, "\n");
    fclose(exit);
}

void main(){
    FILE *entry;
    entry = fopen("entry.txt", "r");
    if(entry == NULL) {
        printf("Error: entry file not found");
        exit(1);
    }

    char rbt[10], fbt[10], fst[10], ng[10], l[10], c[10], so[10];
    if(fscanf(entry, "%s %s %s %s %s %s %s", rbt, fbt, fst, ng, l, c, so) == 7){
        sscanf(rbt, "%d", &RABBITS_BREEDING_TIME);
        sscanf(fbt, "%d", &FOXES_BREEDING_TIME);
        sscanf(fst, "%d", &FOXES_STARVATION_TIME);
        sscanf(ng, "%d", &NUM_GENERATIONS);
        sscanf(l, "%d", &LINES);
        sscanf(c, "%d", &COLUMNS);
        sscanf(so, "%d", &SCENERY_OBJECTS);
    }else{
        printf("ERROR: File format error\n");
        exit(1);
    }

    RABBIT* rabbits = NULL;
    FOX* foxes = NULL;
    char scenery[LINES][COLUMNS];
    
    scenery[LINES][COLUMNS] = creating_scenery(entry, scenery, &rabbits, &foxes);
    printS(scenery, 0);


    for(int i = 0; i < NUM_GENERATIONS; i++){
        if(rabbits != NULL){
            scenery[LINES][COLUMNS] = rabbits_movement(i, scenery, &rabbits);       // RABBIST - MOVING/BREEADING
        }
        if(foxes != NULL){
            scenery[LINES][COLUMNS] = foxes_starvation(scenery, &foxes);            // FOX - STARVATION        
            scenery[LINES][COLUMNS] = foxes_movement(i, scenery, &foxes, &rabbits); // FOX - MOVEMENT/BREADING/HUNTING
        }
        printS(scenery, i+1);
    }
    fclose(entry);
}