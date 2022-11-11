/***************************************************************
*                                                              *
* liblist.c                                                    *
*                                                              *
* Description:                                                 *
*   Implementation of a module to create and manage linked     *
*   lists with items                                           *
*                                                              *
* Bernardo Castelo Branco                                      *   
* https://github.com/bascb                                     *
*                                                              * 
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "liblist.h"

/* defines a list member */
typedef struct list_member {
	struct list_member	*next; /* Pointer to next member */
	void				*item; /* Pointer to member item */
}	Member;

/* defines a list */
struct _list {
	Member	*first; /* Pointer to first member of list */
	Member	*last; /* Pointer to last member of list */
	Member	*current; /* Pointer to current member of list */
	int		total_members; /* Total members in the list */
};

/****************************************************
	Implementation of public functions
****************************************************/

/* Creates a new list */
List	*create_list()
{
	List	*new;

	new = (List *)calloc(1, sizeof(List));
	if (!new)
		return (NULL);

	return (new);
}

/* Append an item to list 
*
* Returns:
*   0 - Item appended with success
*   1 - There is no pointer to item
*   2 - Unable to alloc memory for new list member
* 
*/
int	append_to_list(List *list, void *item)
{
	Member	*new;

	if (!item)
		return (1);

	new = (Member *)calloc(1, sizeof(Member));
	if (!new)
		return (2);

	new->item = item;

	if ( list->first == NULL ) list->first = new;
	else list->last->next = new;

	list->last = new;
	list->total_members++;
	return (0);
}

/* get list size, i.e., total members in the list */
int	list_size(List *list) {
	return (list->total_members);
}

/* Join second list to the end of first list */
void	join_lists(List *first, List *second)
{	
	if (first->last != NULL)
		first->last->next = second->first;
	else
		first->first = second->first;

	first->last = second->last;

	first->total_members += second->total_members;

	free(second);
}

/* Deletes a list
* 
* void (*delete_item)(void *item) - Pointer to function to delete the item
*
*/
void delete_list(List *list, void (*delete_item)(void *item))
{
	Member	*aux;
	Member	*next;

	if (!list)
		return;

	next = list->first;

	while (next != NULL)
	{
		aux = next;
		next = aux->next;
		if (delete_item != NULL)
			delete_item(aux->item);
		free(aux);
	}
	
	free(list);
}

/* Sort list, using bubble sort algorithm
*
* Returns pointer to list if success, otherwise, returns NULL
*
* Compare function int (*cmp)(void *item_a, void *item_b) must return
* a positive value if item a and b are in the right order or 0 if not
*
*/
List	*sort_list(List *list, int (*cmp)(void *item_a, void *item_b))
{
	Member	*present;
	Member	*next;
	int		swap_count;
	void	*aux;

	if (!list || !cmp || !list->first)
		return (NULL);

	swap_count = 1;
	while (swap_count)
	{
		swap_count = 0;
		present = list->first;
		next = present->next;
		while (next)
		{
			if (!cmp(present->item, next->item))
			{
				aux = present->item;
				present->item = next->item;
				next->item = aux;
				swap_count++;
			}
			present = next;
			next = present->next;
		}
	}
	return (list);
}

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
List	*search_in_list(List *list, int (*criterion)(void *item, void *search_params), void *search_params, void *(*duplicate_item)(void *item))
{
	List	*new;
	Member	*next;
	
	if (!list || !criterion || !list->first || !duplicate_item)
		return (NULL);

	new = create_list();
	if (!new)
		return (NULL);

	next = list->first;
	while (next)
	{
		if (criterion(next->item, search_params))
			append_to_list(new, duplicate_item(next->item));
		next = next->next;
	}
	if (!list_size(new))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

/* Removes from list all items that match search criteria
*
* If pointer to delete_item is given, than deletes item 
*
* Returns number of items removed from list, or -1 if ther is no list or no function to check criterion
*
*/
int	remove_from_list(List *list, int (*criterion)(void *item, void *search_params), void *search_params, void (*delete_item)(void *item))
{
	Member	*previous;
	Member	*next;
	int		removed_count;

	if (!list || !criterion || !list->first)
		return (-1);

	removed_count = 0;
	previous = NULL;
	next = list->first;
	while (next)
	{
		if (criterion(next->item, search_params))
		{
			if (delete_item != NULL)
				delete_item(next->item);
			if (!previous)
				list->first = next->next;
			else
				previous->next = next->next;
			free(next);
			removed_count++;
			list->total_members--;
		}
		else
			previous = next;
		if (!previous)
			next = list->first;
		else
			next = previous->next;
		if (!next)
			list->last = previous;
	}
	return (removed_count);
}

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
List	*duplicate_list(List *list, void *(*duplicate_item)(void *item))
{
	List	*new;
	Member	*next;

	if (!list || !list->first)
		return (NULL);

	new = create_list();
	if (!new)
		return (NULL);
	next = list->first;
	while (next)
	{
		if (duplicate_item != NULL)
			append_to_list(new, duplicate_item(next->item));
		else
			append_to_list(new, next->item);
		next = next->next;
	}
	if (!list_size(new))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

/* Get next item of the list 
*
*  Return pointer of next item
*  or NULL if list is in the end
*
*/
void	*get_next_item(List *list)
{
	void	*item = NULL;

	if (!list)
		return (NULL);
	
	if (list->first != NULL)
	{
		if (list->current == list->last)
			list->current = NULL;
		else
		{
			if (list->current != NULL)
				list->current = list->current->next;
			else
				list->current = list->first;
			item = list->current->item;
		}
	}
	return (item);
}

/* Reset the next item to the first of list */
void	reset_list_item(List *list)
{
	if (!list)
		return;
	list->current = NULL;
}
