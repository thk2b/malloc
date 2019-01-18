/*
**	FreeBlock
**	Represents a block vailable for reuses
**	Can be mutated
*/

#ifndef FREE_BLOCK_H
# define FREE_BLOCK_H
# include <shared.h>
# define FREE_BLOCK__MIN_SIZE (sizeof(t_free_block*) * 2 + sizeof(size_t))

# define FREE_BLOCK__BLOCK_COLOR YELLOW
# define FREE_BLOCK__POINTERS_COLOR BLUE
# define FREE_BLOCK__DATA_COLOR WHITE
# define FREE_BLOCK__FOOTER_COLOR BLUE

typedef struct			s_free_block
{
	t_block				block;
	struct s_free_block	*prev;
	struct s_free_block	*next;
/*	char				data[block.size - sizeof(struct s_free_block*) * 2 - sizeof(size_t)]*/
/*	size_t				footer																*/
}						t_free_block;

t_free_block			*free_block__deallocate(t_block *b);
void					free_block__extend(t_free_block *fb, size_t target_size);
void					free_block__remove(t_free_block *fb);
void					free_block__hexdump(t_free_block *fb, size_t index, void *ctx);
# ifdef MALLOC_LOG
void					free_block_log(t_free_block *fb, char *msg);
# endif
#endif
