#ifndef LIB_H
# define LIB_H
# include <shared.h>

# define HX_RESET "\x1b[0m"
# define HX_ADDRESS HX_RESET
# define HX_WIDTH 32

void	put_hex(int fd, size_t n, int prefix);
void	put_dec(int fd, size_t n);
void	put_str(int fd, char *s);
void	hexdump(void *ptr, size_t size, char *color);

#endif
