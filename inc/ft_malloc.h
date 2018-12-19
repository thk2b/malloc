#ifndef				FT_MALLOC
# define			FT_MALLOC
# include			<stddef.h>
# include			<sys/mman.h>

# define ZONE_S_SZ	16
# define ZONE_M_SZ	128

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
}					t_block;

typedef struct		s_page
{
	struct s_page	*next;
	size_t			size;
	size_t			min_block_size;
	t_block			*head;
}					t_page;

extern void			*malloc(size_t size);
extern void			free(void *ptr);
extern void			*realloc(void *ptr, size_t size);
extern void			show_alloc_mem(void);

#endif
