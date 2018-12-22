#include <ft_malloc.h>

int main(void)
{
	char *addr;
	for (int i = 0; i < 1024; i ++)
	{
		addr = malloc(1024);
		addr[0] = 42;
	}
}
