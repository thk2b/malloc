#ifndef SHARED_H
# define SHARED_H
# include <malloc.h>

# define		MIN(a,b) ((a) < (b) ? (a) : (b))
# define		MAX(a,b) ((a) > (b) ? (a) : (b))
# define		ALLIGN(size,allign) (((size) + ((allign) - 1)) & ~((allign) - 1))

#ifdef MALLOC_LOG
# define MALLOC_LOG_PATH "/tmp/.malloc_log"
# endif

#endif
