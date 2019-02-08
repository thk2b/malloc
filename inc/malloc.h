/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:56:30 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/08 07:17:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>

# ifdef LOG
#  define LOG_PATH "/tmp/.malloc_log"
# endif

# define PGS_PER_MAP 28

extern void	*malloc(size_t size);
extern void	*calloc(size_t count, size_t size);
extern void	free(void *ptr);
extern void	*realloc(void *ptr, size_t size);
extern void	show_alloc_mem(void);
extern void	hexdump_mem(void);

#endif
