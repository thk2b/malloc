#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void		init_log(void)
{
	extern int	g_logfd;

	if((g_logfd = open(".malloc_log", O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
		exit(1);
	put_str(g_logfd, "EVENT\t\tADDRESS\t\tSIZE\n");
}

void	malloc_log_new_block(t_block *block)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "new block\t");
	put_hex(g_logfd, (size_t)block, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, block->size);
	put_str(g_logfd, "\n");
}

void	malloc_log_new_area(t_area *area)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "new area\t");
	put_hex(g_logfd, (size_t)area, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, area->size);
	put_str(g_logfd, "\n");
}

void	malloc_log_extended_area(t_area *area)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "extended area\t");
	put_hex(g_logfd, (size_t)area, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, area->size);
	put_str(g_logfd, "\n");
}
