#include <malloc.h>

/*
**	find an allocated block given its address
**	==
**	for each alocated area
**		if ptr is in range(area, area + area.size)
**			for each block
**				if block.data == ptr
**					return block
**	return nil
*/

t_block		*find_block(void *ptr)
{
	(void)ptr;
	return (NULL);
}
