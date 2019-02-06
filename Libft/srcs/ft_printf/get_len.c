/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 23:01:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 19:10:49 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "libft.h"

void			init_len(t_convertion_len *len)
{
	len->left_spaces = 0;
	len->sign = 0;
	len->prefix = 0;
	len->zeros = 0;
	len->value = 0;
	len->right_spaces = 0;
	len->total = 0;
}

static size_t	get_zeros(t_convertion_len *len, t_directive *d, size_t total)
{
	if (d->convertion == 's' || d->convertion == 'S')
		return (0);
	if (d->precision > (int)total)
		len->zeros = d->precision - total;
	return (len->zeros);
}

void			get_len(t_convertion_len *len,
	t_directive *d, size_t val_len, int sign)
{
	size_t total;

	total = val_len;
	init_len(len);
	total += get_zeros(len, d, total);
	if (ft_strchr("Ddi", d->convertion))
		if (sign == -1 || d->flags & (F_SPACE | F_PLUS))
			len->sign = 1;
	total += len->sign;
	if (d->flags & F_HASH && ((val_len && sign != 0) || d->flags & F_PTR
		|| (ft_strchr("oO", d->convertion) && d->precision != -1)))
		len->prefix = ft_strchr("Xx", d->convertion) ? 2 : 1;
	total += len->prefix;
	if ((unsigned)d->width > total)
	{
		if (d->flags & F_ZERO && d->precision == -1)
			len->zeros += d->width - total;
		else if (d->flags & F_MINUS)
			len->right_spaces = d->width - total;
		else
			len->left_spaces = d->width - total;
		total += d->width - total;
	}
	len->value = val_len;
	len->total = total;
}
