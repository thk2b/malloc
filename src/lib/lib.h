#ifndef LIB_H
# define LIB_H
# include <shared.h>

void	put_hex(int fd, size_t n, int prefix);
void	put_dec(int fd, size_t n);
void	put_str(int fd, char *s);

#endif
