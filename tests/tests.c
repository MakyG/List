/**
 * @file       tests.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Tests source file that tests functions of ADT list
 * **********************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

/* Private includes -------------------------------------------------------- */
#include <inttypes.h>
#include <string.h>
#include "../src/list.h"
#include "minunit.h"

////////////////////////////// IMPORTANT ///////////////////////////////////////
/////////// Source repository: https://github.com/siu/minunit //////////////////
/////////// For more info consult with this page ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MU_TEST(test_initialize_list) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  mu_assert(listArray->first == NULL && listArray->active == NULL,
            "Initializing array failed.");
  free(listArray);
}

MU_TEST(test_initialize_list_nulls) { List_Init(NULL); }

MU_TEST(test_insert_first) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
    mu_assert_int_eq(
        0, memcmp(&listArray->first->data, &dataList, sizeof(dataList)));
  }
  {
    Data_t dataList = {
        .age = 35, .weight = 78, .height = 176, .name = "Catherine"};
    List_Insert_First(listArray, dataList);
    mu_assert_int_eq(
        0, memcmp(&listArray->first->data, &dataList, sizeof(dataList)));
  }

  while (listArray->first != NULL) {
    List_Delete_First(listArray);
  }

  free(listArray);
}

MU_TEST(test_insert_first_nulls) {
  Data_t dataList = {.age = 35, .weight = 78, .height = 176, .name = "Catherine"};
  List_Insert_First(NULL, dataList);
}

MU_TEST(test_delete_first) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
    mu_assert_int_eq(
        0, memcmp(&listArray->first->data, &dataList, sizeof(dataList)));
  }
  {
    Data_t dataList = {
        .age = 35, .weight = 78, .height = 176, .name = "Catherine"};
    List_Insert_First(listArray, dataList);
    mu_assert_int_eq(
        0, memcmp(&listArray->first->data, &dataList, sizeof(dataList)));
  }
  List_Delete_First(listArray);
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
  mu_assert_int_eq(
      0, memcmp(&listArray->first->data, &dataList, sizeof(dataList)));
  List_Delete_First(listArray);
  mu_assert(listArray->first == NULL,
            "List_Delete_First with last item called should be NULL.");
  free(listArray);
}

MU_TEST(test_delete_first_nulls) { List_Delete_First(NULL); }

MU_TEST(test_copy_first) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
  Data_t dataListCopy;
  List_Insert_First(listArray, dataList);
  mu_assert(List_Copy_First(*listArray, &dataListCopy),
            "List_Copy_First copy wasnt successful.");
  mu_assert_int_eq(0, memcmp(&dataList, &dataListCopy, sizeof(dataList)));
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_copy_first_nulls) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  List_Copy_First(*listArray, NULL);
}

MU_TEST(test_post_delete) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
  }
  {
    Data_t dataList = {.age = 47, .weight = 83, .height = 178, .name = "Tanner"};
    List_Insert_First(listArray, dataList);
    List_First(listArray);
    mu_assert(strcmp(dataList.name, listArray->first->data.name) == 0,
              "Wrong first item in a list.");
  }
  List_Post_Delete(listArray);
  mu_assert(listArray->first->next == NULL,
            "Deleting item after the first one failed.");
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_post_delete_nulls) { List_Post_Delete(NULL); }

MU_TEST(test_post_insert) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
  }
  {
    Data_t dataList = {.age = 24, .weight = 69, .height = 168, .name = "Luke"};
    List_Post_Insert(listArray, dataList);
    mu_assert(listArray->first->next == NULL,
              "No item was active, there should be not an new item in list.");
    List_First(listArray);
    mu_assert_string_eq("John", listArray->first->data.name);
    List_Post_Insert(listArray, dataList);
    mu_assert_int_eq(
        0, memcmp(&dataList, &listArray->first->next->data, sizeof(dataList)));
  }

  while (listArray->first != NULL) {
    List_Delete_First(listArray);
  }

  free(listArray);
}

MU_TEST(test_post_insert_nulls) {
  Data_t dataList = {.age = 24, .weight = 69, .height = 168, .name = "Luke"};
  List_Post_Insert(NULL, dataList);
}

MU_TEST(test_list_copy) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  Data_t dataListCopy;
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
  List_Insert_First(listArray, dataList);
  List_First(listArray);
  mu_assert(listArray->first == listArray->active,
            "First item should be active!");
  mu_assert(List_Copy(*listArray, &dataListCopy),
            "There is an active item! Return value should be true.");
  mu_assert_int_eq(0, memcmp(&dataList, &dataListCopy, sizeof(dataList)));
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_list_copy_no_active) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  Data_t dataListCopy = {.name = "test"};
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
  List_Insert_First(listArray, dataList);
  mu_assert(!List_Copy(*listArray, &dataListCopy),
            "No active item! Returned value should be false.");
  mu_assert(listArray->active == NULL, "The active item should still be NULL");
  mu_assert(
      0 != memcmp(&listArray->first->data, &dataListCopy, sizeof(dataListCopy)),
      "Tha values should be different!");
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_list_actualize) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
  }
  Data_t dataList = {.age = 24, .weight = 75, .height = 149, .name = "Johnny"};
  List_First(listArray);
  List_Actualize(listArray, dataList);
  mu_assert_int_eq(
      0, memcmp(&listArray->active->data, &dataList, sizeof(dataList)));
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_list_actualize_no_active) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
  }
  Data_t dataList = {.age = 24, .weight = 75, .height = 149, .name = "Johnny"};
  List_Actualize(listArray, dataList);
  mu_assert(0 != memcmp(&listArray->first->data, &dataList, sizeof(dataList)),
            "The values should be different.");
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST(test_list_actualize_nulls) {
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
  List_Actualize(NULL, dataList);
}

MU_TEST(test_list_succ) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  {
    Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "John"};
    List_Insert_First(listArray, dataList);
  }
  {
    Data_t dataList = {.age = 36, .weight = 72, .height = 167, .name = "Gregor"};
    List_Insert_First(listArray, dataList);
  }
  {
    Data_t dataList = {.age = 19, .weight = 56, .height = 158, .name = "Anna"};
    List_Insert_First(listArray, dataList);
  }
  List_First(listArray);
  mu_assert(listArray->first == listArray->active,
            "First item should be active!");
  List_Succ(listArray);
  mu_assert(listArray->first->next == listArray->active,
            "The second item should be active!");
  List_Succ(listArray);
  mu_assert(listArray->first->next->next == listArray->active,
            "The third item should be active!");
  List_Succ(listArray);
  mu_assert(listArray->active == NULL, "The active item should be NULL!");
  List_Succ(listArray);
  mu_assert(listArray->active == NULL, "The active item should be NULL!");
  while (listArray->first != NULL) {
    List_Delete_First(listArray);
  }
  free(listArray);
}

MU_TEST(test_list_succ_nulls) { List_Succ(NULL); }

MU_TEST(test_is_active) {
  List_t *listArray = malloc(sizeof(List_t));
  List_Init(listArray);
  Data_t dataList = {.age = 23, .weight = 70, .height = 150, .name = "Catherine"};
  List_Insert_First(listArray, dataList);
  mu_assert(!List_Is_Active(*listArray), "There should be not an active item!");
  List_First(listArray);
  mu_assert(List_Is_Active(*listArray), "There should be an active item!");
  List_Delete_First(listArray);
  free(listArray);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_initialize_list);
  MU_RUN_TEST(test_initialize_list_nulls);
  MU_RUN_TEST(test_insert_first);
  MU_RUN_TEST(test_insert_first_nulls);
  MU_RUN_TEST(test_delete_first);
  MU_RUN_TEST(test_delete_first_nulls);
  MU_RUN_TEST(test_copy_first);
  MU_RUN_TEST(test_copy_first_nulls);
  MU_RUN_TEST(test_post_delete);
  MU_RUN_TEST(test_post_delete_nulls);
  MU_RUN_TEST(test_post_insert);
  MU_RUN_TEST(test_post_insert_nulls);
  MU_RUN_TEST(test_list_copy);
  MU_RUN_TEST(test_list_copy_no_active);
  MU_RUN_TEST(test_list_actualize);
  MU_RUN_TEST(test_list_actualize_nulls);
  MU_RUN_TEST(test_list_actualize_no_active);
  MU_RUN_TEST(test_list_succ);
  MU_RUN_TEST(test_list_succ_nulls);
  MU_RUN_TEST(test_is_active);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();

  return 0;
}
