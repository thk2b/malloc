#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# define MALLOC_LOG 1

/*
**	Exported API
*/

extern void		*malloc(size_t size);
extern void		*calloc(size_t count, size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem(void);
extern void		dump_mem(void);

/*
*	Block
**		Represents a single allocation
*/

typedef struct	s_block
{
	size_t		free:1;
	size_t		size:sizeof(size_t) - 1;
}				t_block;

/*
**	Free block
*/

typedef struct	s_fblock
{
	t_block			block;
	struct s_fblock	*prev;
	struct s_fblock	*next;
}				t_fblock;

/*
**	Area
**		Represents a memoy area obtained via mmap
*/

typedef struct	s_area
{
	size_t			size;
	size_t			cur_size;
	struct s_area	*next;
}				t_area;

# define		N_FREE_LISTS 3
typedef struct	s_free_list
{
	size_t		min_size;
	t_fblock	*head;
}				t_free_list;

/*
**	core
*/

# define		MIN(a,b) ((a) < (b) ? (a) : (b))
# define		MAX(a,b) ((a) > (b) ? (a) : (b))
# define		ALLIGN(size,allign) (((size) + ((allign) - 1)) & ~((allign) - 1))
# define		MIN_BLOCK_SIZE ALLIGN((sizeof(struct s_free_list*) * 2), 8)
# define		MIN_AREA_SIZE(pgsz) ((pgsz) * 2)
# define		DATA(b) ((char*)(b) + sizeof(t_block))
# define		AREA_AVAILABLE_SIZE(a) ((a)->size - (a)->cur_size)
# define		AREA_END(a) ((void*)((char*)(a) + (a)->size))
# define		AREA_CUR_END(a) ((void*)((char*)(a) + (a)->cur_size))
# define		AREA_HEAD(a) ((t_block*)((char*)(a) + sizeof(t_area)))
# define		BLOCK_NEXT(b) ((t_block*)((char*)(b) + sizeof(t_block) + (b)->size))

t_area			*new_area(size_t size);
t_area			*find_area_with_available_size(size_t size);
t_fblock		*find_free_block(size_t size);
t_block			*find_block(void *ptr);
void			free_list_insert();

#ifdef MALLOC_LOG

void			init_log(void);
void			malloc_log_new_block(t_block *block);
void			malloc_log_new_area(t_area *area);

#endif

/*
**	lib.c
*/

void			put_hex(int fd, size_t n, int prefix);
void			put_dec(int fd, size_t n);
void			put_str(int fd, char *s);

/*
**	hexdump
*/

# define		HEXDUMP_WIDTH	32
# define		RESET			"\x1b[0m"
# define		BLACK			"\x1b[30m"
# define		RED				"\x1b[31m"
# define		GREEN			"\x1b[32m"
# define		BLUE			"\x1b[34m"
# define		YELLOW			"\x1b[33m"
# define		CYAN			"\x1b[36m"
# define		WHITE			"\x1b[37m"

#define			BG_WHITE "\x1b[47m"
#define			BG_RED "\xbb[42m"
#define			BG_GREEN "\x1b[42m"
#define			BG_YELLOW "\x1b[43m"
#define			BG_BLUE "\x1b[44m"
#define			BG_MAGENTA "\x1b[46m"
#define			BG_CYAN "\x1b[47m"

# define		ADDRESS					""
# define		BLOCK_HEADER			YELLOW
# define		BLOCK_DATA				GREEN
# define		FREE_LIST_NODE			BLUE
# define		FREE_BLOCK_REMAINDER	RED
# define		AREA_HEADER				BLACK CYAN
# define		AREA_UNUSED				WHITE

#endif
