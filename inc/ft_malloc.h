#ifndef				FT_MALLOC
# define			FT_MALLOC
# include			<stddef.h>
# include			<sys/mman.h>
# include			<unistd.h>

#include <stdio.h> //

# define ALLIGN(size) (((size) + (8 - 1)) & ~(8 - 1))

# define PAGES_PER_MAP		2
# define NZONES		3
# define ZONE_S_SZ	16
# define ZONE_M_SZ	128

# define IS_FREE(block) (block->data == NULL)

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	void			*data;
}					t_block;

typedef struct		s_page
{
	struct s_page	*next;
	size_t			size;
	size_t			cur_size;
	size_t			min_block_size;
	t_block			*head;
}					t_page;

extern void			*malloc(size_t size);
extern void			free(void *ptr);
extern void			*realloc(void *ptr, size_t size);
extern void			show_alloc_mem(void);

/*
**	block.c
*/

void				init_block(t_block *block, t_block *prev, size_t size);
t_block				*append_new_block(t_page *page, t_block *prev, size_t size);
int					split_block(t_block *block);

/*
**	get_free_block.c
*/

t_block				*get_free_block(t_page *zone, size_t size);

/*
**	page.c
*/

t_page				*append_page(t_page *page);

/*
**	get_zone.c
*/

t_page				*get_zone(size_t size);

#endif
