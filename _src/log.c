#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#ifdef MALLOC_LOG

void	sigsegv(int s)
{
	extern int	g_logfd;
	static int	c = 0;

	if (g_logfd != -1)
	{
		put_str(g_logfd, "caught signal ");
		put_dec(g_logfd, s);
		put_str(g_logfd, "\n");
	}
	if (c == 0)
	{
		dump_mem();
		c++;
	}
	exit(1);
}

void		init_log(void)
{
	extern int	g_logfd;

	signal(SIGSEGV, sigsegv);
	signal(SIGABRT, sigsegv);
	signal(SIGBUS, sigsegv);
	if((g_logfd = open(MALLOC_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
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
	static size_t	count = 0;
	if (g_logfd == -1)
		init_log();
	put_dec(g_logfd, count++);
	put_str(g_logfd, " ");
	put_str(g_logfd, message);
	put_str(g_logfd, "\t");
	put_hex(g_logfd, (size_t)block, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, block->size);
	put_str(g_logfd, "\n");
}

void	malloc_log_malloc(size_t size)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "\tmalloc\t");
	put_dec(g_logfd, size);
	put_str(g_logfd, "\n");
}

void	malloc_log_free(void *ptr)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "\tfree\t");
	put_hex(g_logfd, (size_t)ptr, 1);
	put_str(g_logfd, "\n");
}

void	malloc_log_realloc(void *ptr, size_t size)
{
	extern int	g_logfd;

	if (g_logfd == -1)
		init_log();
	put_str(g_logfd, "\trealloc\t");
	put_hex(g_logfd, (size_t)ptr, 1);
	put_str(g_logfd, "\t");
	put_dec(g_logfd, size);
	put_str(g_logfd, "\n");
}

#endif
