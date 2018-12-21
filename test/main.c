#include <ft_malloc.h>
#include <string.h>

int main(void)
{
	char *s = malloc(1);
	char *t = malloc(1);
	strcpy(s, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	puts(s);
	puts(t);
	show_alloc_mem();
}
