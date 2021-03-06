#include <malloc.h>
#ifdef LOG
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <shared.h>

static void	sig_handler(int sig)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(2, "Caught signal ");
	put_dec(2, (size_t)sig);
	put_str(2, "\n");
	put_str(fd, "Caught signal ");
	put_dec(fd, (size_t)sig);
	put_str(fd, "\n");
	// show_alloc_mem();
	// hexdump_mem();
	close(fd);
	exit(1);
}

static void	open_log(int *fd)
{
	*fd = open(LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (*fd == -1)
		error__log_open_failed();
	put_str(*fd, "ID\tEVENT\t\tENTITY\t\tADDRESS\t\tSIZE\n");
	signal(SIGSEGV, sig_handler);
	signal(SIGABRT, sig_handler);
}

void		log__line_count(int fd)
{
	static int	c = 0;

	put_dec(fd, c++);
	put_str(fd, "\t");
}

int			log__get_fd(void)
{
	static int	fd = 0;

	if (fd == 0)
		open_log(&fd);
	return (fd);
}

#endif
