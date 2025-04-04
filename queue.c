#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void enqueue(struct queue *q, struct game_state state) {
    int spot = serialize(state);
    insert_at_tail((&q -> data),spot);

}

struct game_state dequeue(struct queue *q) {
    remove_from_head(&q -> data);
    
    return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    struct list_node* new_node = (struct list_node*)malloc(sizeof(struct list_node));
    new_node -> next = NULL;

    if (q -> data.head == NULL){
        q -> data.head = new_node;
    }

    while (q -> data.head != NULL) {
        struct game_state curr = dequeue(q);
        if (start == curr) {
            return curr;
        } else {
            for (node child in children(curr)) {
                enqueue(&q, child);
            }
        }
    }

    return 0; 
}
