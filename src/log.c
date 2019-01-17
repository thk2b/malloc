# include <malloc.h>

#ifdef LOG
# include <fcntl.h>
# include <shared.h>

static void	open_log(int *fd)
{
	*fd = open(LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (*fd == -1)
		error__log_open_failed();
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
