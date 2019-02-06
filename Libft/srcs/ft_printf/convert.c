/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:13:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/13 23:33:50 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directive.h"
#include "convert.h"
#include "libft.h"
#include "style.h"
#include <stdarg.h>

static unsigned long long	cast_u_arg(va_list ap, t_directive *d)
{
	if (d->length == 'l')
		return ((unsigned long)va_arg(ap, unsigned long));
	if (d->length == 'L')
		return ((unsigned long long)va_arg(ap, unsigned long long));
	if (d->length == 'h')
		return ((unsigned short)va_arg(ap, int));
	if (d->length == 'H')
		return ((unsigned char)va_arg(ap, int));
	if (d->length == 'z')
		return ((size_t)va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}

static long long			cast_s_arg(va_list ap, t_directive *d)
{
	if (d->length == 'l')
		return ((long)va_arg(ap, long));
	if (d->length == 'L')
		return ((long long)va_arg(ap, long long));
	if (d->length == 'h')
		return ((short)va_arg(ap, int));
	if (d->length == 'H')
		return ((char)va_arg(ap, int));
	if (d->length == 'z')
		return ((size_t)va_arg(ap, size_t));
	return (va_arg(ap, int));
}

int							convert(t_directive *d, char **dst, va_list ap)
{
	if (ft_strchr("dDi", d->convertion))
		return (convert_ll_base(10, dst, cast_s_arg(ap, d), d));
	if (d->convertion == 'x' || d->convertion == 'X')
		return (convert_ull_base(16, dst, cast_u_arg(ap, d), d));
	if (d->convertion == 'o' || d->convertion == 'O')
		return (convert_ull_base(8, dst, cast_u_arg(ap, d), d));
	if (d->convertion == 'b' || d->convertion == 'B')
		return (convert_ull_base(2, dst, cast_u_arg(ap, d), d));
	if (d->convertion == 'u' || d->convertion == 'U')
		return (convert_ull_base(10, dst, cast_u_arg(ap, d), d));
	if (d->convertion == 's')
		return (convert_str(dst, va_arg(ap, char*), d, 0));
	if (d->convertion == 'S')
		return (convert_wstr(dst, va_arg(ap, wchar_t*), d, 0));
	if (d->convertion == 'c')
		return (convert_char(dst, va_arg(ap, int), d));
	if (d->convertion == 'C')
		return (convert_wchar(dst, va_arg(ap, wchar_t), d));
	if (d->convertion == '{')
		return (convert_style(dst, d));
	if (d->convertion == '%')
		return (convert_percent(dst, d));
	return (0);
}
