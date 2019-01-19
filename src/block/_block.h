/*
**	Block
**	Represents an area of memory satisfying a unique request
**	Is immutable, the size and contents cannot be altered
*/

#ifndef _BLOCK_H
# define _BLOCK_H
# include <shared.h>
# include <stdint.h>

# define BLOCK__DATA(b) ((void*)((char*)(b) + sizeof(t_block)))
# define BLOCK__NEXT(b) ((t_block*)((char*)(b) + (b)->size + sizeof(t_block)))
# define BLOCK__GET_PREV_FOOTER(b) ((size_t*)((char*)(b) - sizeof(size_t)))
# define BLOCK__PREV(b) ((t_block*)((char*)b - *BLOCK__GET_PREV_FOOTER(b) - sizeof(t_block)))

# define BLOCK__HEADER_COLOR YELLOW
# define BLOCK__DATA_COLOR GREEN

typedef struct	s_block
{
	size_t		prev_free:1;
	size_t		free:1;
	size_t		size:sizeof(size_t) * 8 - 2;
	// uint8_t		chksum;
}				t_block;

t_block			*block__allocate(void *addr, size_t size);
t_block			*block__from_ptr(void *addr);
void			block__deallocate_prev(t_block *b);
void			block__allocate_prev(t_block *b);
void			block__show_alloc(t_block *b, size_t index, void *ctx);
void			block__hexdump(t_block *b, size_t index, void *ctx);

int				block__find_address(t_block *b, void *ctx);

# ifdef LOG
void			block__log(t_block *b, char *msg);
# endif
#endif
