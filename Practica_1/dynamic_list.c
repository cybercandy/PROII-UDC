/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * DATE: 25 / 02 / 22
 */

#include "dynamic_list.h"
bool createNode(tPosL* p);

/* **************************** DYNAMIC LIST **************************** */

void createEmptyList(tList* L){
    *L = LNULL;
}

bool createNode(tPosL* p){
    *p = malloc(sizeof(**p));
    return (*p != LNULL); /* if there is memory returns true */
}

bool isEmptyList(tList L){
    return (L == LNULL);
}

tPosL first(tList L){
    return L; /* L is a pointer to the first element of the list */
}

tPosL last(tList L){
    tPosL p;
    for(p = L; p->next != NULL; p = p->next)
        ;
    return p;
}

tPosL next(tPosL p, tList L){
    if (p->next == NULL)
        return LNULL;
    else
        return (p->next);
}

tPosL previous(tPosL p, tList L){
    tPosL i;
    if (p == first(L))
        return LNULL;
    else{
        i = first(L);
        for(i = first(L); i->next != NULL && i->next != p; i = i->next)
            ;
        if(i->next == p)
            return i;
        else
            return LNULL;
    }
}

bool insertItem(tItemL d, tPosL p, tList* L){
    tPosL q, r;
    if(!createNode (&q)) {
        return false;
    }else{
        q->data = d;
        q->next = LNULL;

        if (*L == LNULL) //L is empty
            *L = q;
            //L is a pointer to the first element
        else // L is not empty
        {
            if (p == LNULL) //the given position is NULL
            {
                for (r = *L; r->next != LNULL; r = r->next); //we move r until the last node created
                r->next = q;
            }
            else //the given position is not NULL
            {
                if (p == *L)
                {
                    q->next = p;
                    *L = q;
                }
                else
                {
                    q->data = p->data;
                    p->data = d;
                    q->next = p->next;
                    p->next = q;
                }
            }
        }
        return true;
    }
}

void deleteAtPosition (tPosL p, tList* L){
    tPosL q;
    if (p == *L)
        *L = p->next;
    else
    if(p->next == LNULL)
    {
        for(q=*L; q->next != p; q=q->next)
            ;
        q->next = LNULL;
    }
    else
    {
        for(q=*L; q->next != p; q=q->next);
        q->next = p->next;
    }
}

tItemL getItem(tPosL p, tList L){
    return (p->data);
}

void updateItem(tItemL n, tPosL p, tList* L){
    p->data = n;
}

tPosL findItem(tProductId d, tList L){
    tPosL p;
    for(p = L; ((p != NULL) && (strcmp(p->data.productId, d) != 0) /*it has to be in this order bc the first part of
 * the AND is checked first, and then the second one*/); p = p->next)
        ;
    return p;
}