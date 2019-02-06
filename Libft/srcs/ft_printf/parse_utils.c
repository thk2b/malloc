/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:07:27 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 16:08:22 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "directive.h"
#include "parse.h"

int	parse_flags(t_directive *d, const char *fmt)
{
	int	len;

	len = 0;
	while (1)
	{
		if (fmt[len] == '#')
			d->flags |= F_HASH;
		else if (fmt[len] == '-')
			d->flags |= F_MINUS;
		else if (fmt[len] == '+')
			d->flags |= F_PLUS;
		else if (fmt[len] == ' ')
			d->flags |= F_SPACE;
		else if (fmt[len] == '0')
		{
			if (d->flags & F_MINUS)
				break ;
			d->flags |= F_ZERO;
		}
		else
			break ;
		len++;
	}
	return (len);
}

int	parse_length(t_directive *d, const char *fmt)
{
	if (ft_strncmp(fmt, "hh", 2) == 0)
		d->length = 'H';
	else if (*fmt == 'h')
		d->length = 'h';
	else if (ft_strncmp(fmt, "ll", 2) == 0)
		d->length = 'L';
	else if (*fmt == 'l')
		d->length = 'l';
	else if (*fmt == 'j')
		d->length = 'j';
	else if (*fmt == 'z')
		d->length = 'z';
	if (d->length >= 'A' && d->length <= 'Z')
		return (2);
	if (d->length >= 'a' && d->length <= 'z')
		return (1);
	return (0);
}
