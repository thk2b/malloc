#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef MALLOC_LOG

void		init_log(void)
{
	extern int	g_logfd;

	if((g_logfd = open("/tmp/.malloc_log", O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
	{
		write(2, "can't open log\n", 16);
		exit(1);
	}
	put_str(g_logfd, "EVENT\t\tADDRESS\t\tSIZE\n");
}

void	malloc_log_area(t_area *area, char *message)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, message);
	put_str(g_logfd, "\t");
	put_hex(g_logfd, (size_t)area, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, area->size);
	put_str(g_logfd, "\n");	
}

void	malloc_log(t_block *block, char *message)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, message);
	put_str(g_logfd, "\t");
	put_hex(g_logfd, (size_t)block, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, block->size);
	put_str(g_logfd, "\n");	
}

#endif
