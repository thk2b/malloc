/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:40:33 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/13 23:34:11 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "directive.h"
#include "parse.h"
#include "style.h"

static void	reset_directive(t_directive *d)
{
	d->convertion = 0;
	d->flags = 0;
	d->length = 0;
	d->precision = -1;
	d->width = 0;
}

static int	parse_width(t_directive *d, const char *fmt, va_list ap)
{
	int len;

	len = 0;
	if (fmt[len] == '*')
	{
		d->width = va_arg(ap, int);
		return (1);
	}
	if (ft_isdigit(*fmt))
	{
		d->width = ft_atoi(fmt);
		while (ft_isdigit(fmt[len]))
			len++;
		return (len);
	}
	return (0);
}

static int	parse_precision(t_directive *d, const char *fmt, va_list ap)
{
	int len;

	if (*fmt != '.')
		return (0);
	len = 1;
	if (fmt[len] == '*')
	{
		d->precision = va_arg(ap, int);
		return (2);
	}
	if (ft_isdigit(fmt[len]))
	{
		d->precision = ft_atoi(fmt + len);
		while (ft_isdigit(fmt[len]))
			len++;
		return (len);
	}
	else
		d->precision = 0;
	return (len);
}

static int	parse_convertion(t_directive *d, const char *fmt)
{
	if (*fmt == 'p')
	{
		d->flags |= (F_HASH | F_PTR);
		d->length = 'L';
		d->convertion = 'x';
		return (1);
	}
	if ((*fmt == 's' || *fmt == 'c') && d->length == 'l')
	{
		d->convertion = *fmt - 'a' + 'A';
		return (1);
	}
	if (ft_strchr("DOUB", *fmt))
		d->length = 'l';
	d->convertion = *fmt;
	return (1);
}

int			parse(t_directive *d, const char *fmt, va_list ap)
{
	int len;

	reset_directive(d);
	if (*fmt == '{')
		return (parse_style(d, fmt, ap));
	len = 0;
	len += parse_flags(d, fmt + len);
	len += parse_width(d, fmt + len, ap);
	len += parse_precision(d, fmt + len, ap);
	len += parse_length(d, fmt + len);
	len += parse_convertion(d, fmt + len);
	return (len);
}
