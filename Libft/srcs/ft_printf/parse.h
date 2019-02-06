/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 10:53:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/13 14:06:52 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "directive.h"
# include <stdarg.h>
# define IS_FLAG(c) ((c) == '#' || (c) == ' ' || (c) == '-' || (c) == '+')

int	parse_flags(t_directive *d, const char *fmt);
int	parse_length(t_directive *d, const char *fmt);
int	parse(t_directive *directive, const char *fmt, va_list ap);

#endif
