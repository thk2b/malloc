#ifndef BLOCK_H
# define BLOCK_H
# include <shared.h>
# include <stdint.h>

typedef struct	s_block
{
	size_t		prev_free:1;
	size_t		free:1;
	size_t		size:sizeof(size_t) * 8 - 2;
	uint8_t		chksum;
}				t_block;

void			*block__data(t_block *block);
t_block			*block__allocate(void *addr, size_t size);

#endif
