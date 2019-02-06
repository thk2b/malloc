/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:04:52 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 16:04:43 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "libft.h"

static unsigned long long	get_pow(int base,
	unsigned long long ull, size_t *ndigits)
{
	unsigned long long	pow;
	unsigned long long	npow;
	size_t				len;

	pow = 1;
	len = 1;
	while ((npow = pow * base) <= ull && npow > pow)
	{
		pow = npow;
		len++;
	}
	*ndigits = len;
	return (pow);
}

static int					get_sign(long long ll)
{
	if (ll < 0)
		return (-1);
	if (ll == 0)
		return (0);
	return (1);
}

int							convert_ull_base(int base,
	char **dst, unsigned long long ull, t_directive *d)
{
	t_convertion_len	len;
	unsigned long long	pow;
	size_t				ndigits;
	char				*t;

	ndigits = 0;
	pow = get_pow(base, ull, &ndigits);
	if (ull == 0 && d->precision != -1)
		ndigits = 0;
	get_len(&len, d, ndigits, ull > 0);
	if ((*dst = (char*)malloc(sizeof(char) * len.total)) == NULL)
		return (-1);
	t = *dst;
	t += set_pre(t, &len, d, 0);
	if (ndigits)
		t += ISUPPER(d->convertion) ? set_up_digits(base, t, ull, pow)
			: set_low_digits(base, t, ull, pow);
	set_post(t, &len, d);
	return (len.total);
}

int							convert_ll_base(int base,
	char **dst, long long ll, t_directive *d)
{
	t_convertion_len	len;
	unsigned long long	pow;
	unsigned long long	ull;
	size_t				ndigits;
	char				*t;

	ull = ll < 0 ? (unsigned long long)(-1 * ll) : (unsigned long long)ll;
	ndigits = 0;
	pow = get_pow(base, ull, &ndigits);
	if (ull == 0 && d->precision != -1)
		ndigits = 0;
	get_len(&len, d, ndigits, get_sign(ll));
	if ((*dst = (char*)malloc(sizeof(char) * len.total)) == NULL)
		return (-1);
	t = *dst;
	t += set_pre(t, &len, d, ll < 0);
	if (ndigits)
		t += ISUPPER(d->convertion) ? set_up_digits(base, t, ull, pow)
			: set_low_digits(base, t, ull, pow);
	set_post(t, &len, d);
	return (len.total);
}
