#ifndef LIB_H
# define LIB_H
# include <shared.h>

# define HX_RESET "\x1b[0m"
# define HX_ADDRESS HX_RESET
# define HX_WIDTH 32
# define HEXDUMP_WIDTH 32
# define RESET "\x1b[0m"
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define YELLOW "\x1b[33m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

void	put_hex(int fd, size_t n, int prefix);
void	put_dec(int fd, size_t n);
void	put_str(int fd, char *s);
void	hexdump(void *ptr, size_t size, char *color);

#endif
