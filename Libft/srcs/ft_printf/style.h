/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 21:07:29 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/13 23:33:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLE_H
# define STYLE_H
# include "directive.h"
# include <stdarg.h>

# define S_EOC 1
# define S_RED 2
# define S_GREEN 4
# define S_BLUE 8
# define S_BLACK 16
# define S_WHITE 32
# define S_YELLOW 64
# define S_CYAN 128
# define S_BOLD 256
# define S_INVERT 512
# define S_UNDERLINED 1024

int	parse_style(t_directive *directive, const char *fmt, va_list ap);
int	convert_style(char **dst, t_directive *directive);

#endif
