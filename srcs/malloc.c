#include <ft_malloc.h>
#include <unistd.h>

extern void	*malloc(size_t size)
{
	char a = 'a';
	write(1, &a, 1);
	(void)size;
	return (NULL);
}
