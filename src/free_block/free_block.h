/*
**	FreeBlock
**	Represents a block vailable for reuses
**	Can be mutated
*/

#ifndef FREE_BLOCK_H
# define FREE_BLOCK_H
# include <shared.h>

typedef struct			s_free_block
{
	t_block				block;
	struct s_free_block	*next;
	struct s_free_block	*prev;
/*	char				data[block.size - sizeof(struct s_free_block*) * 2 - sizeof(size_t)]*/
/*	size_t				footer																*/
}						t_free_block;

t_free_block			*free_block__deallocate(t_block *b, t_free_block *prev);
void					free_block__extend(t_free_block *fb, size_t target_size);
void					free_block__remove(t_free_block *fb);
void					free_block__hexdump(t_free_block *fb);
# ifdef MALLOC_LOG
void					free_block_log(t_block_list *fb, char *msg);
# endif
#endif
