#include <ft_malloc.h>

t_page	g_zones[] = {
	{NULL, 0, 0, 0, NULL},
	{NULL, 0, 0, ZONE_S_SZ + 1, NULL},
	{NULL, 0, 0, ZONE_M_SZ + 1, NULL},
};
