/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * DATE: 01 / 04 / 22
 */

#include "product_list.h"

tList createEmptyList(tList *L) {
    *L = LNULL;
    return (*L);
}

bool createNode(tPosL *p) {
    *p = malloc(sizeof(struct tNode));
    return (*p != LNULL);  /* if there is memory returns true */
}

bool isEmptyList(tList L) {
    return (L == LNULL);
}

tPosL first(tList L) {
    return L; /* L is a pointer to the first element of the list */
}

tPosL last(tList L) {
    tPosL p;
    for (p = L; p->next != LNULL; p = p->next);
    return p;
}

tPosL next(tPosL p, tList L) {
    if(p->next == LNULL)
        return LNULL;
    else
        return (p->next);
}

tPosL previous(tPosL p, tList L) {
    tPosL i;
    if (p == first(L))
        return LNULL;
    else {
        for (i = first(L); i->next != LNULL && i->next != p ; i = i->next)
            ;
        if(i->next == p)
            return i;
        else
            return LNULL;
    }
}

//Auxiliar function used in insertItem
tPosL findPosition(tList L, tItemL d) {
    tPosL p;
    p = L;
    while ((p->next != LNULL) && (strcmp(p->next->data.productId, d.productId) < 0))
        p = p->next;
    return p;
}


bool insertItem(tItemL d, tList *L) {
    tPosL q, r;
    if (!createNode(&q))
        return false;
    else {
        q->data = d;
        q->next = LNULL;

        if (*L == LNULL) { //L is empty
            *L = q; //L is a pointer to the first element

            //
        }else if (strcmp(d.productId, (*L)->data.productId) < 0) {
            q->next = *L;
            *L = q; //inserts at the end
        } else {     //find the position
            r = findPosition(*L, d);
            q->next = r->next;  //assigns NULL if we insert it at the end
            r->next = q;
        }
        return true;
    }
}



tList deleteAtPosition(tPosL p, tList *L) {

    tPosL q;
    if (p == *L) { //checks if it is the first position
        *L = p->next; //what was before in the first position now is in the second one
    } else if (p->next == LNULL) {
        for (q = *L; q->next != p; q = q->next); /* goes through the list until the position
 before p and we make the next position to that one equal NULL, leave p outside */
        q->next = LNULL; //becomes last position
    } else {
        q = p->next; //we have eliminated the last position, so moves one position forward every user
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);

}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

tList updateItem(tItemL d, tPosL p, tList *L) {
    p->data = d;
    return (*L);
}

tPosL findItem(tProductId d, tList L) {
    tPosL p;
    if (isEmptyList(L)){
        return LNULL;}
    else {
        for (p = L; ((p != LNULL) && (strcmp(p->data.productId, d) < 0)); p = p->next)
            ;
        if (p != LNULL && strcmp(p->data.productId, d) == 0)
            return p;
        else
            return LNULL;

    }
}