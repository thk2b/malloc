#include <ft_malloc.h>
#include <stdio.h>

extern void	*malloc(size_t size)
{
	printf("A");
	(void)size;
	return (NULL);
}
