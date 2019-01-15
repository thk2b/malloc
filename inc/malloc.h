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
	size_t		prev_free:1;
	size_t		free:1;
	size_t		size:sizeof(size_t) * 8 - 2;
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

size_t			free_list_index(size_t block_size);//TODO:macro or inline
void			free_list_insert(t_fblock *fblock);
void			free_list_insert_after(t_fblock *prev, t_fblock *fblock);
void			free_list_remove(t_fblock *fblock);
/*
**	errors
*/

void			*error_ptr_was_not_allocated(void *ptr);

/*
**	core
*/

# define		MIN(a,b) ((a) < (b) ? (a) : (b))
# define		MAX(a,b) ((a) > (b) ? (a) : (b))
# define		ALLIGN(size,allign) (((size) + ((allign) - 1)) & ~((allign) - 1))
# define		FREE_LIST_NODE_SIZE ((sizeof(struct s_fblock*) * 2))
# define		MIN_BLOCK_SIZE (FREE_LIST_NODE_SIZE + sizeof(size_t))
# define		MIN_AREA_SIZE(pgsz) ((pgsz) * 2)
# define		DATA(b) ((char*)(b) + sizeof(t_block))
# define		AREA_AVAILABLE_SIZE(a) ((a)->size - (a)->cur_size)
# define		AREA_END(a) ((void*)((char*)(a) + (a)->size))
# define		AREA_CUR_END(a) ((void*)((char*)(a) + (a)->cur_size))
# define		AREA_HEAD(a) ((t_block*)((char*)(a) + sizeof(t_area)))
# define		AREA_CAN_FIT(a, s) ((a)->cur_size + s <= (a)->size)
# define		AREA_PTR_IS_IN_RANGE(a, addr) ((void*)(addr) >= (void*)AREA_HEAD(a) && (void*)(addr) < (void*)AREA_CUR_END(a))
# define		BLOCK_NEXT(b) ((t_block*)((char*)(b) + sizeof(t_block) + (b)->size))
# define		BLOCK_PREV(b) ()

t_area			*new_area(size_t size);
t_area			*find_area_with_available_size(size_t size);
t_area			*find_area_fblock(t_fblock *fblock);
t_fblock		*find_free_block(size_t size);
t_block			*find_block(void *ptr, t_fblock **prev_fblock, t_area **area);
t_fblock		*split_block(t_block *block, size_t size);
t_block			*extend_block(t_block *block, size_t size, t_fblock **last_free_block, t_area *area);

#ifdef MALLOC_LOG

void			init_log(void);
void			malloc_log_new_block(t_block *block);
void			malloc_log_new_area(t_area *area);
void			malloc_log_extended_area(t_area *area);
void			malloc_log_freed_block(t_block *block);
void			malloc_log_allocated_free_block(t_block *block);
void			malloc_log_coalesced(t_block *block);
void			malloc_log_extended_block(t_block *block);
void			malloc_log_split_block(t_block *block);
void			malloc_log_reaped_block(t_block *block);

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
# define		FREE_BLOCK_REMAINDER	WHITE
# define		FREE_BLOCK_FOOTER		YELLOW
# define		AREA_HEADER				BLACK CYAN
# define		AREA_UNUSED				WHITE

#endif
