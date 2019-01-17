#include <lib.h>

void	hexdump(void *ptr, size_t size, char *color)
{
	static size_t	count = 0;
	size_t			i;
	unsigned char	n;
	unsigned char	*d;

	if (ptr == NULL)
	{
		count = 0;
		return ;
	}
	i = 0;
	d = (unsigned char*)ptr;
	while (i < size)
	{
		if (count == 0)
		{
			put_str(1, HX_ADDRESS);
			put_hex(1, (size_t)(d + i), 0);
			put_str(1, " ");
			put_str(1, HX_RESET);
		}
		put_str(1, color);
		while (i < size && count++ < HX_WIDTH)
		{
			n = d[i];
			i += 1;
			put_hex(1, (size_t)n, 0);
			if (n < 16)
				put_str(1, "0");
			put_str(1, " ");
		}
		if (i >= size)
			break ;
		count = 0;
		put_str(1, HX_RESET "\n");
	}
	put_str(1, HX_RESET);
}

#ifdef TEST
int		main(int ac, char **av)
{
	hexdump((void*)av, ac * sizeof(char*), "");
}
#endif
