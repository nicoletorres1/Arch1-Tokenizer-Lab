#include <stdlib.h>
#include <stdio.h>
#include "history.h"



/* Initialize the linked list to keep the history. */
List* init_history()
{
  // Malloc a list pointer
  List * newList = (List*) malloc(sizeof(List));
  
  // Set the list pointer's root to be NULL
  newList->root = NULL;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str)
{ 
  // Create a new item with the string from the parameter we want to store
  Item * newItem = (Item*) malloc(sizeof(Item));
  newItem->str = str;
  newItem->id = 1;
  newItem->next = NULL;
  
  // If the list is empty
  if(list->root == NULL)
  {
    // We set the first element of the list (root) to be the new item
    list->root = newItem;
    return;
  }
  
  // Start at the beginning of the list
  Item * current = list->root;
  
  // Iterate until we reach the last node of the list
  while (current->next != NULL)
  {
    current = current->next;
    newItem->id++;
  }
  // Increment to next id after last
  newItem->id++;
  // Set the "next" of the end of the list to be our new item
  current->next = newItem;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  // Start at the beginning of the list
  Item * current = list->root;
  
  // Iterate until we reach the desired id or the last node of the list
  while (current != NULL)
  {
    // If the current Item's id is equal to the desired id, return the string of the Item
    if (current->id == id)
    {
      // Return the string associated with current
      return current->str;
    }
    current = current->next;
  }
  // If we never find the desired ID, we return null
  return NULL;
}

/* Print the entire contents of the list. */
void print_history(List *list)
{
  // Start at the beginning of the list
  Item * current = list->root;
  
  // Iterate until we reach the last node of the list
  while (current != NULL)
  {
    // Print the id and str of the current item
    printf("ID: %d, STR: %s\n",current->id, current->str);
    current = current->next;
  }
}

/* Free the history list and the strings it references. */
void free_history(List *list)
{
  // While our list is not empty
  while (list->root != NULL)
  {
    // Free the end of the list
    
    // If there is only one node left in the list
    if (list->root->next == NULL)
    {
      // Free the first node's string
      free(list->root->str);
      // Free the first node
      free(list->root);
      // Set our first node to NULL
      list->root = NULL;
      
      // Free the list itself
      free(list);
      
      return;
    }
    
    // Start at the beginning of the list
    Item * current = list->root;

    // Iterate until we reach the second to last node of the list
    while (current->next->next != NULL)
    {
      current = current->next;
    }
    // Free the end of the list's string
    free(current->next->str);
    // Free the end of the list
    free(current->next);
    // Set the second to last node to point to null
    current->next = NULL;
  }
}
