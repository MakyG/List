/**
 * @file       list.h
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Header file of linear list
 * **********************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

#ifndef LIST_H
#define LIST_H

/* Public includes --------------------------------------------------------- */
#include <stdbool.h>
#include "data.h"
#include "mymalloc.h"

/** @struct List_Node_s
 * Definition of one item in a list
 *
 * @var typedef List_Node_s List_Node_t
 * @var typedef List_Node_t * List_Node_Ptr_t
 */
typedef struct List_Node_s {
  Data_t data;              /**< DATA part of an item */
  struct List_Node_s* next; /**<	pointer at next item */
} List_Node_t;

typedef List_Node_t* List_Node_Ptr_t;

/** @struct List_t
 * Definition of list as a pointer at first and active item.
 *
 */
typedef struct {
  List_Node_t* first;  /**< Pointer at first item in list */
  List_Node_t* active; /**< Pointer at active item in list */
} List_t;

/* Public List_t API ------------------------------------------------------- */
/**
 * @brief       Initializes the list, set List_t#first list->first &
 * List_t#active list->active with NULL pointers
 * @param[in]   list    List, which we want to initialize
 */
void List_Init(List_t* const list);
//
/**
 * @brief Creates a new item and puts it at the start of the list, active item
 * stays the same.
 * @param[in] list - list, where to store the new item
 * @param[in] data - data to store in new item
 */
void List_Insert_First(List_t* const list, Data_t data);

/**
 * @brief Set active item pointer at the first item in the list. List_t#active
 * list->active at value List_t#first list->first
 * @param[in] list - Pointer at list, where we want to set the first item as
 * active
 */
void List_First(List_t* const list);

/**
 * @brief Returns data of the first item
 * @param list[in] - list, with which the operation should be done
 * @param *data[out] - pointer, where are data being stored
 * @return Returns true, if the value is read, return false otherwise
 */
bool List_Copy_First(List_t list, Data_t* data);

/**
 * @brief Deletes the first item in list, if the FIRST was also the ACTIVE item,
 * the active item will be NULL, if the list is empty, nothing happens
 * @param[in] list - list, with which the operation should be done
 */
void List_Delete_First(List_t* const list);

/**
 * @brief Deletes the item that is after the active item in a list, if theres no
 * active item or list is empty, nothing happens.
 * @param[in] list - list, with which the operation should be done
 */
void List_Post_Delete(List_t* const list);

/**
 * @brief Inserts new item after the active item in a list. If theres no active
 * item, nothing happens.
 * @param list[in] - list, with which the operation should be done
 * @param data[in] - data to store in a list
 */
void List_Post_Insert(List_t* const list, Data_t data);

/**
 * @brief Return the data from an active item
 * @param list[in] - list, with which the operation should be done
 * @param *data[out] - pointer, where are the data being stored
 * @return Returns true if the item was copied, otherwise return false
 */
bool List_Copy(List_t list, Data_t* data);

/**
 * @brief Updates the data of an active item, if theres no active item, nothing
 * happens
 * @param list[in] - list, with which the operation should be done
 * @param data[in] - data, which are being stored
 */
void List_Actualize(const List_t* const list, Data_t data);

/**
 * @brief Shifts the active item to the next one, if theres no active item,
 * nothing happens
 * @param list[in] - list, with which the operation should be done
 */
void List_Succ(List_t* const list);

/**
 * @brief If theres an active item, return true, return false otherwise
 * @param list[in] - list, with which the operation should be done
 */
bool List_Is_Active(List_t list);

#endif /* LIST_H */
