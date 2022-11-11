/***************************************************************
*                                                              *
* liblist.h                                                    *
*                                                              *
* Description:                                                 *
*   Interface of a module to create and manage linked          *
*   lists with items                                           *
*                                                              *
* Bernardo Castelo Branco                                      *   
* https://github.com/bascb                                     *
*                                                              * 
***************************************************************/

#ifndef LIBLIST_H
# define LIBLIST_H

typedef struct _list	List;

/* Creates a new list */
List	*create_list();

/* Append an item to list 
*
* Returns:
*   0 - Item appended with success
*   1 - There is no pointer to item
*   2 - Unable to alloc memory for new list member
* 
*/
int	append_to_list(List *list, void *item);

/* get list size, i.e., total members in the list */
int	list_size(List *list);

/* Join second list to the end of first list */
void	join_lists(List *first, List *second);

/* Deletes a list
* 
* void (*delete_item)(void *item) - Pointer to function to delete the item
*
*/
void delete_list(List *list, void (*delete_item)(void *item));

/* Sort list, using bubble sort algorithm
*
* Returns pointer to list if success, otherwise, returns NULL
*
* Compare function int (*cmp)(void *item_a, void *item_b) must return
* a positive value if item a and b are in the right order or 0 if not
*
*/
List	*sort_list(List *list, int (*cmp)(void *item_a, void *item_b));

/* search items in list that meet the given criterion
*
*  Returns a pointer to a new list with selected items
*  or NULL if the new list is an empty list
*
* Criterion check function int (*criterion)(void *item, void *search_params)
* must return a positive value if item matches the search
* criterion or 0 if not
*
*/
List	*search_in_list(List *list, int (*criterion)(void *item, void *search_params), void *search_params, void *(*duplicate_item)(void *item));

/* Removes from list all items that match search criteria
*
* If pointer to delete_item is given, than deletes item 
*
* Returns number of items removed from list, or -1 if ther is no list or no function to check criterion
*
*/
int	remove_from_list(List *list, int (*criterion)(void *item, void *search_params), void *search_params, void (*delete_item)(void *item));

/* Duplicates a list
*
* Returns a pointer to the new list
* Returns NULL if:
* - A list is not supplied
* - Function is unable to allocate memory to the new list
* - New list is empty
*
* The function void *(*duplicate_item)(void *item), if supplied,
* must return a pointer to the new item or NULL on error.
*
* If it is supplied a pointer to a function to duplicate an item,
* the new list will have duplicated items, otherwise, will point to the same
* items that are pointed by the original list.
*
* Attention: If it is supplied a pointer to a function to duplicate an item,
* only successfully duplicated items will be added to the new list
*	
*/
List	*duplicate_list(List *list, void *(*duplicate_item)(void *item));

/* Get next item of the list 
*
*  Return pointer of next item
*  or NULL if list is in the end
*
*/
void	*get_next_item(List *list);

/* Reset the next item to the first of list */
void	reset_list_item(List *list);

#endif
