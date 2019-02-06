/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:13:50 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 19:12:59 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "libft.h"

int	convert_str(char **dst, char *src, t_directive *d, int is_char)
{
	t_convertion_len	len;
	size_t				cur;
	size_t				srclen;

	cur = 0;
	if (src == NULL)
		src = "(null)";
	srclen = is_char ? 1 : ft_strlen(src);
	srclen = d->precision && srclen > (unsigned)d->precision
		? (unsigned)d->precision : srclen;
	get_len(&len, d, srclen, 0);
	if ((*dst = (char*)malloc(sizeof(char) * len.total)) == NULL)
		return (-1);
	cur += set_pre(*dst, &len, d, 0);
	ft_strncpy(*dst + cur, src, srclen);
	cur += srclen;
	cur += set_post(*dst + cur, &len, d);
	return (cur);
}

int	convert_char(char **dst, char src, t_directive *d)
{
	return (convert_str(dst, &src, d, 1));
}
