/***************************************************************
*                                                              *
* test_list.c                                                  *
*                                                              *
* Description:                                                 *
*  A simple program to test liblist shared library             *
*                                                              *
* Bernardo Castelo Branco                                      *   
* https://github.com/bascb                                     *
*                                                              * 
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <liblist.h>

void	print_list(List *list, char *title)
{
	int	*number;

	printf("%s as a size of: %i\n", title, list_size(list));
	while ((number = get_next_item(list)) != NULL)
		printf("%i ", *number);
	printf("\n");
}

void	*duplicate_number(void *origin)
{
	int	*dup;

	dup = calloc(1, sizeof(int));
	if (!dup)
		return (NULL);
	*dup =*((int *) origin);
	return (dup);
}

int	sort_asc(void *a, void *b)
{
	return (*((int *) a) <= *((int *) b));
}

int	sort_desc(void *a, void *b)
{
	return (*((int *) a) >= *((int *) b));
}

int	main(void)
{
	int		i;
	int		n;
	int		*number;
	int		reference;
	int		removed;
	List	*random;
	List	*asc;
	List	*desc;
	List	*less;
	List	*more;
	time_t	t;

	n = 20;
	srand((unsigned) time(&t));
	random = create_list();
	reference = 50;
	i = 0;
	while (i++ < n)
	{
		number = calloc(1, sizeof(int));
		if (!number)
			continue;
		*number = rand() % 100;
		add_to_list(random, number);
	}
	print_list(random, "Random list:");
	asc = duplicate_list(random, duplicate_number);
	sort_list(asc, sort_asc);
	print_list(asc, "Sorted in ascending order:");
	desc = duplicate_list(random, duplicate_number);
	sort_list(desc, sort_desc);
	print_list(desc, "Sorted in descending order:");
	less = search_in_list(random, sort_asc, &reference, duplicate_number);
	sort_list(less, sort_asc);
	print_list(less, "<= 50:");
	more = search_in_list(random, sort_desc, &reference, duplicate_number);
	sort_list(more, sort_asc);
	print_list(more, ">= 50:");
	join_lists(less, more);
	print_list(less, "Joined again:");
	removed = remove_from_list(random, sort_asc, &reference, free);
	printf("Removed %i numbers from random list\n", removed);
	sort_list(random, sort_asc);
	print_list(random, "Random list:");
	delete_list(random, free);
	delete_list(asc, free);
	delete_list(desc, free);
	delete_list(less, free);
	return (0);
}
