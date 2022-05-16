/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * DATE: 01 / 04 / 22
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdbool.h>

#define SNULL -1
#define STACK_SIZE 25

typedef int tPosS;

typedef struct tItemS{
    tUserId bidder;
    tProductPrice productPrice;
}tItemS;

typedef struct tStack{
    tPosS top;
    tItemS array[STACK_SIZE];
}tStack;


tStack createEmptyStack(tStack *s);
/*
 * Goal: Creates an empty stack.
 * Input: s: Stack to be created.
 * Output: An empty stack.
 * Postcondition: The stack has no elements.
 * */

bool push(tItemS item, tStack *s);
/*
 * Goal: Insert an element at the top of the stack.
 * Input: item: Element to be inserted.
 *        s: Stack where we are inserting.
 * Output: true if it could be inserted, false otherwise.
 * Precondition: The stack is initialised.
 * Postcondition: The positions of the elements in the subsequent stack may have varied.
 * */

void pop(tStack *s);
/*
 * Goal: Removes from the stack the element located at its top.
 * Input: s: Stack to be modified.
 * Output: Stack without the element located at the top.
 * Precondition: The stack is not empty and previously initialised.
 * Postcondition: The positions of the elements in the subsequent stack may have varied.
 * */

tItemS peek(tStack s);
/*
 * Goal: Recovers the content of the element at the top of the stack without removing it.
 * Input: s: Stack from where the item is to be retrieved.
 * Output: Content of the element located at the top of the stack.
 * Precondition: The stack is not empty and previously initialised.
 * */

bool isEmptyStack(tStack s);
/*
 * Goal: Determines if the stack is empty or not.
 * Input: s: Stack to be checked.
 * Output: true if the stack is empty, false otherwise.
 * Precondition: The stack is initialised.
 * */

#endif
