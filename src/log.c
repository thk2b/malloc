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

int			log__get_fd(void)
{
	int	fd = 0;

	if ((fd = 0))
		open_log(&fd);
	return (fd);
}

#endif
