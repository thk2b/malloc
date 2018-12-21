#include <ft_malloc.h>
#include <string.h>

int main(void)
{
	char *s = malloc(8);
	char *t = malloc(8);
	strcpy(s, "1");
	// puts(s);
	// puts(t);
	show_alloc_mem();
}
