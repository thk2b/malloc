/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:48:52 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 15:45:24 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "libft.h"
#include <printf.h>

static size_t	repeat(size_t n, char c, char *dst)
{
	size_t	cur;

	cur = 0;
	while (cur < n)
		dst[cur++] = c;
	return (n);
}

static size_t	set_prefix(t_directive *d, char *dst)
{
	if (ft_strchr("xX", d->convertion))
	{
		*(dst) = '0';
		*(dst + 1) = d->convertion == 'x' ? 'x' : 'X';
		return (2);
	}
	*dst = '0';
	return (1);
}

static size_t	set_sign(t_directive *d, char *dst, int is_neg)
{
	if (is_neg == 0 && (d->flags & (F_SPACE | F_PLUS)))
	{
		*dst = d->flags & F_PLUS ? '+' : ' ';
		return (1);
	}
	else if (is_neg)
	{
		*dst = '-';
		return (1);
	}
	return (0);
}

size_t			set_pre(char *dst,
	t_convertion_len *len, t_directive *d, char is_neg)
{
	size_t cur;

	(void)d;
	cur = 0;
	if (len->left_spaces)
		cur += repeat(len->left_spaces, ' ', dst);
	if (len->sign)
		cur += set_sign(d, dst + cur, is_neg);
	if (len->prefix)
		cur += set_prefix(d, dst + cur);
	if (len->zeros)
		cur += repeat(len->zeros, '0', dst + cur);
	return (cur);
}

size_t			set_post(char *dst, t_convertion_len *len, t_directive *d)
{
	size_t cur;

	(void)d;
	cur = 0;
	if (len->right_spaces)
		cur += repeat(len->right_spaces, ' ', dst);
	return (cur);
}
