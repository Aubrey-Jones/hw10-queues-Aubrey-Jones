#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct visited_states {
    uint64_t *states;
    size_t count;
    size_t capacity;
};

void initialize_visited(struct visited_states *visited, size_t initial_capacity){
    visited -> states = malloc(initial_capacity * sizeof(uint64_t));
    visited -> count = 0;
    visited -> capacity = initial_capacity;
}

void free_visited(struct visited_states *visited){
    free(visited -> states);
}

bool is_state_visited(struct visited_states *visited, uint64_t state){
    for (size_t i = 0; i < visited -> count; i++){
        if (visited -> states[i] == state){
            return true;
        }
    }
    return false;
}

void mark_state_as_visited(struct visited_states *visited, uint64_t state){
    if (visited -> count >= visited -> capacity){
        visited -> capacity *= 2;
        visited -> states = realloc(visited -> states, visited -> capacity * sizeof(uint64_t));
    }
    visited -> states[visited -> count++] = state;
}

bool is_goal(struct game_state state){
    int goal[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,0}
    };

    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            if (state.tiles[row][col] != goal[row][col]){
                return false;
            }
        }
    }
    return true;
}

bool is_valid(struct game_state state){
    if (state.empty_row < 0 || state.empty_row >= 4 || state.empty_col < 0 || state.empty_col >= 4){
        return false;
    }

    bool seen[16] = {false};
    for (int row=0; row < 4; row++){
        for (int col=0; col < 4; col++){
            int value = state.tiles[row][col];
            if (value < 0 || value > 15){
                return false;
            }
            if (seen[value]){
                return false;
            }
            seen[value] = true;
        }
    }
    return true;
}

void create_queue(struct queue *q){
    q -> data.head = NULL;
}

bool is_empty(struct queue *q){
    return ((q -> data.head) == NULL);
}

void enqueue(struct queue *q, struct game_state state) {
    uint64_t ser_state = serialize(state);
    insert_at_tail(&q -> data,ser_state);
}

struct game_state dequeue(struct queue *q) {
    if (is_empty(q)){
        return (struct game_state){0}; 
    }   
    uint64_t ser_state = remove_from_head(&q -> data);
    return deserialize(ser_state);
}

int number_of_moves(struct game_state start) {
    struct visited_states visited = {0};
    initialize_visited(&visited, 100);

    struct queue q = {0};
    create_queue(&q);
    enqueue(&q, start);
    mark_state_as_visited(&visited,serialize(start));

    while (!is_empty(&q)){
        struct game_state current = dequeue(&q);

        if (is_goal(current)){
            free_visited(&visited);
            return current.num_steps;
        }

        struct game_state next_states[4];
        next_states[0] = current; move_up(&next_states[0]);
        next_states[1] = current; move_down(&next_states[1]);
        next_states[2] = current; move_left(&next_states[2]);
        next_states[3] = current; move_right(&next_states[3]);

        for (int i=0; i < 4; i++){
            uint64_t ser_state = serialize(next_states[i]);
            if (is_valid(next_states[i]) && (!is_state_visited(&visited,ser_state))){
                mark_state_as_visited(&visited, ser_state);
                enqueue(&q, next_states[i]);
            }
        }
    }
    free_visited(&visited);
    return -1;
}
