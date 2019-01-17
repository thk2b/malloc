#ifndef AREA_H
# define AREA_H

typedef struct		s_area
{
	struct s_area	*next;
	struct s_area	*prev;
	size_t			size;
	size_t			cur_size;
}					t_area;

typedef t_area		*(*area__search_fn)(t_area *a, void *ctx);

#endif
