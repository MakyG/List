/**
 * @file       list.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Implementing functions of ATD list defined in a header file
 * list.h
 * ****************************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

/* Private includes -------------------------------------------------------- */
#include "list.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions definitions --------------------------------------------------- */

void List_Init(List_t* const list) {
    if(!list)
        return;

    list->first = list->active = NULL;
}

void List_Insert_First(List_t* const list, Data_t data) {
    if(!list)
        return;

    List_Node_t* newFirst = myMalloc(sizeof(List_Node_t));
    if(!newFirst)
        return;

    newFirst->data = data;
    newFirst->next = list->first;

    list->first = newFirst;

}

void List_First(List_t* const list) {
    if(!list)
        return;
    list->active = list->first;
}

bool List_Copy_First(List_t list, Data_t* data) {
    if(!data)
        return false;
    if(!list.first)
        return false;
    *data = list.first->data;
    return true;
}

void List_Delete_First(List_t* const list) {
    if(!list)
        return;
    if(!list->first)
        return;
    if(list->first == list->active)
        list->active = NULL;
    List_Node_t* lateNext = list->first->next;

    myFree(list->first);
    list->first = lateNext;
}

void List_Post_Delete(List_t* const list) {
    if(!list)
        return;
    if(!list->active)
        return;
    if(!list->active->next)
        return;
    List_Node_t* lateNext = list->active->next->next;
    myFree(list->active->next);
    list->active->next = lateNext;
}

void List_Post_Insert(List_t* const list, Data_t data) {
    if(!list)
        return;
    if(!list->active)
        return;
    List_Node_t* newFirst = myMalloc(sizeof(List_Node_t));

    if(!newFirst)
        return;
    newFirst->data = data;
    newFirst->next = list->active->next;

    list->active->next = newFirst;
}


bool List_Copy(List_t list, Data_t* data) {
    if(!data)
        return false;
    if(!list.active)
        return false;

    *data = list.active->data;
    return true;
}

void List_Actualize(const List_t* const list, Data_t data) {
    if(!list)
        return;
    if(!list->active)
        return;

    list->active->data = data;
}

void List_Succ(List_t* const list) {
    if(!list)
        return;
    if(!list->active)
        return;

    list->active = list->active->next;
}

bool List_Is_Active(List_t list) {
    return list.active;
}
