#include <free_list.h>
#include <area_list.h>

t_area_list	g_area_list = {
	NULL, NULL, 0
};

t_free_list	g_free_lists[FL__N_FREE_LISTS] = {
	{NULL, 0},
	{NULL, 256},
	{NULL, 1024}
}
