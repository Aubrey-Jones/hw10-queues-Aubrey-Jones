#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>

#define GRID_SIZE 4

typedef struct {
    int correctRow;
    int correctCol;
} goalSingle;

typedef struct{
    int currentRow;
    int currentCol;
    goalSingle target;
} currentGame;

struct goalSingle {
    
};

bool isCorrectValue(currentGame *tile){
    return (tile -> currentRow == tile -> target.correctRow) && (tile -> currentCol == tile -> target.correctCol);
}


void enqueue(struct queue *q, struct game_state state) {
    int spot = serialize(state);
    insert_at_tail((&q -> data),spot);

}

struct game_state dequeue(struct queue *q) {
    remove_from_head(&q -> data);
    
    return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) {
    uint64_t buff = serialize(start);
    struct game_state state = deserialize(buff);



    return 0; 
}
