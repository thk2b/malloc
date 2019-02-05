/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:33:32 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:33:32 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <shared.h>

# ifdef HEXDUMP_BG
#  ifndef HEXDUMP_WIDTH
#   define HEXDUMP_WIDTH 320
#  endif
# else
#  ifndef HEXDUMP_WIDTH
#   define HEXDUMP_WIDTH 32
#  endif
# endif

# define RESET "\x1b[0m"

# define BG_BLACK "\x1b[40m"
# define BG_RED "\x1b[41m"
# define BG_GREEN "\x1b[42m"
# define BG_BLUE "\x1b[44m"
# define BG_YELLOW "\x1b[43m"
# define BG_CYAN "\x1b[46m"
# define BG_WHITE "\x1b[47m"

# define TXT_BLACK "\x1b[30m"
# define TXT_RED "\x1b[31m"
# define TXT_GREEN "\x1b[32m"
# define TXT_BLUE "\x1b[34m"
# define TXT_YELLOW "\x1b[33m"
# define TXT_CYAN "\x1b[36m"
# define TXT_WHITE "\x1b[37m"

# define HEXDUMP_ADDRESS RESET

# ifdef HEXDUMP_BG
#  define BLACK TXT_BLACK BG_BLACK
#  define RED TXT_RED GB_RED
#  define GREEN TXT_GREEN BG_GREEN
#  define BLUE TXT_BLUE BG_BLUE
#  define YELLOW TXT_YELLOW BG_YELLOW
#  define CYAN TXT_CYAN BG_CYAN
#  define WHITE TXT_WHITE BG_WHITE
# else
#  define BLACK TXT_BLACK
#  define RED TXT_RED
#  define GREEN TXT_GREEN
#  define BLUE TXT_BLUE
#  define YELLOW TXT_YELLOW
#  define CYAN TXT_CYAN
#  define WHITE TXT_WHITE
# endif

void	put_hex(int fd, size_t n, int prefix);
void	put_dec(int fd, size_t n);
void	put_str(int fd, char *s);
void	hexdump(void *ptr, size_t size, char *color);

#endif
