#ifndef FREE_BLOCK_H
# define FREE_BLOCK_H
# include <shared.h>
# include <block.h>

typedef struct			s_free_block
{
	t_block				block;
	struct s_free_block	*next;
	struct s_free_block	*prev;
}						t_free_block;

void					free_block__new(t_block *b, t_free_block *prev);
void					free_block__extend(t_free_block *fb, size_t target_size);
void					free_block__remove(t_free_block *fb);

#endif
