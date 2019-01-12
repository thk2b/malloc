#include <malloc.h>

/*
**	root of the area list
*/

t_area	*g_area_head = NULL;
t_area	*g_area_tail = NULL;

/*
**	free lists
*/

t_free_list g_free_lists[N_FREE_LISTS] = {
	{ 0		, NULL	},
	{ 56	, NULL	},
	{ 256	, NULL	}
};
