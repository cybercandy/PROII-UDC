/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * DATE: 01 / 04 / 22
 */

#include "bid_stack.h"

tStack createEmptyStack(tStack *s){
    s->top = SNULL;
    return *s;
}

bool push(tItemS item, tStack *s){
    if(s->top == STACK_SIZE-1) {
        return false;
    }else {
        s->array[++s->top] = item;
    }
    return true;
}

void pop(tStack *s){
    s->top--;
}


tItemS peek(tStack s){
    return s.array[s.top];
}

bool isEmptyStack(tStack s){
    if(s.top == SNULL)
        return true;
    else
        return false;
}