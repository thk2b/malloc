#ifndef SHARED_H
# define SHARED_H
# include <malloc.h>
# include <_block.h>
# include <free_block.h>
# include <area.h>
# include <area_list.h>
# include <free_list.h>
# include <lib.h>

# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define MAX(a,b) ((a) > (b) ? (a) : (b))
# define ALLIGN(size,allign) (((size) + ((allign) - 1)) & ~((allign) - 1))
# define UNUSED(v) ((void)(v))

int		log__get_fd(void);
void	log__line_count(int fd);

void	*error__no_mem(void);
void	error__ptr_was_not_allocated(void *ptr);
void	error__log_open_failed(void);

#endif
