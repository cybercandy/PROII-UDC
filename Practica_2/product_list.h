/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * DATE: 01 / 04 / 22
 */

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include "bid_stack.h"
#include <stdlib.h>
#include <string.h>

#define LNULL NULL

typedef struct tItemL{
    tProductId productId;
    tUserId seller;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
}tItemL;

typedef struct tNode* tPosL;
struct tNode{
    tItemL data;
    tPosL next;
}tNode;
typedef tPosL tList;


tList createEmptyList(tList* L);
/*
 * Goal: Creates an empty list
 * Input: L: List to be created
 * Output: An empty list
 * Postcondition: The list has no elements and is initialized
 */

bool isEmptyList(tList L);
/*
 * Goal: Determines if the list is empty
 * Input: L: List to be checked
 * Output: true if the list is empty, false otherwise
 */

tPosL first(tList L);
/*
 * Goal: Returns the position of the first element of the list
 * Input: L: List to be handled
 * Output: Position of the first element
 * Precondition: The list is not empty
 */

tPosL last(tList L);
/*
 * Goal: Returns the position of the last element of the list
 * Input: L: List to be handled
 * Output: Position of the last element
 * Precondition: The list is no empty
 */


tPosL next(tPosL p, tList L);
/*
 * Goal:  Returns the position of the element that follows the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the next element, or LNULL if the given element is the last one
 * Precondition: p is a valid position in the list
 */

tPosL previous(tPosL p, tList L);
/*
 * Goal: Returns the position of the element preceding the current one
 * Input: p: Position of the current element
 *        L: List to be handled
 * Output: Position of the previous element, or LNULL if the given element is the first one
 * Precondition: p is a valid position in the list
 */


bool insertItem(tItemL d, tList *L);
/*
 * Goal: Inserts an element in the list following a given data ordering criterion
 *      on the tItemL field.
 * Input: d: Contents of the element to be inserted
 *        L: List where we are inserting
 *        pNode: Position taken as reference for the insertion
 * Output: List with the element d inserted as its corresponding position
 *          and true if it could be inserted, false otherwise
 * Precondition: The list is initialized
 * Postcondition: The positions of the elements in the list subsequent to the inserted one may have varied.
 */


tList deleteAtPosition(tPosL p, tList* L);
/*
 * Goal: Deletes the element with the given position from the list
 * Input: p: Position of the element to delete
 *        L: List to be modified
 * Output: List without the element that was located at position p
 * Precondition: p is a valid position in the list and the bid stack of the product is empty
 * Postcondition: The positions of the elements in the list subsequent to the deleted one may have varied.
 */

tItemL getItem(tPosL p, tList L);
/*
 * Goal: Retrieves the content of an element of the list
 * Input: p: Position of the desired element
 *        L: List from where the item is to be retrieved
 * Output: Content of the element located at position p
 * Precondition: p is a valid position in the list
 */

tList updateItem(tItemL d, tPosL p, tList* L);
/*
 * Goal: Modifies the content of an element of the list
 * Input: d: New content to be assigned to the element at position p
          p: Position of the element that we wish to modify
          L: The list to be modified
 * Output: List with the content of the element modified
 * Precondition: p is a valid position in the list
 */


tPosL findItem(tProductId d, tList L);
/*
 * Goal: Finds the first element with a specified content in the list
 * Input: d: Content of the element to search for
 *        L: List where the search is to be made
 * Output: Position of the element found, or LNULL if it is not found
 */



#endif
