#include <unistd.h>
#include <stdlib.h>

void	put_hex(int fd, size_t n, int prefix)
{
	char		buf[67] = {0};
	static char	sym[] = "0123456789abcdef";
	size_t		n_div;
	size_t		div;
	size_t		i;

	if (prefix)
	{
		buf[0] = '0';
		buf[1] = 'x';
	}
	div = 1;
	while ((n_div = div * 16) <= n && n_div > div)
		div = n_div;
	i = prefix ? 2 : 0;
	while (div)
	{
		buf[i++] = sym[n / div % 16];
		div /= 16;
	}
	write(fd, buf, i);
}

void	put_dec(int fd, size_t n)
{
	char		buf[64] = {0};
	static char	sym[] = "0123456789";
	size_t		n_div;
	size_t		div;
	size_t		i;

	div = 1;
	while ((n_div = div * 10) <= n && n_div > div)
		div = n_div;
	i = 0;
	while (div)
	{
		buf[i++] = sym[n / div % 10];
		div /= 10;
	}
	write(fd, buf, i);
}

void	put_str(int fd, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

#ifdef TEST
# include <stdio.h>
# include <limits.h>

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	put_hex(1, SIZE_MAX - 1);
	printf("\n%#lx\n", SIZE_MAX - 1);
	put_dec(1, SIZE_MAX);
	printf("\n%zu\n", SIZE_MAX);
}
#endif
