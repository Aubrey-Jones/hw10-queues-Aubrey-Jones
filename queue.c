#include "queue.h"
#include "tile_game.h"


void enqueue(struct queue *q, struct game_state state) {
    int spot = serialize(state);
    insert_at_tail((&q -> data),spot);

}

struct game_state dequeue(struct queue *q) {
    remove_from_head(&q -> data);
    
    return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) {
    struct queue *q;
    struct list_node value;
    (q -> data.head) = NULL;
    while (q->data.head != NULL) {
        dequeue(q);
        if (equals(cur, search)) {
            return cur;
        } else {
            for (node child in children(cur)) {
                enqueue(&q, child);
            }
        }
    }

    return 0; 
}
