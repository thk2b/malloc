/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_digits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:03:20 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 16:03:46 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

int	set_up_digits(int base,
	char *dst, unsigned long long ull, unsigned long long pow)
{
	static char	*sym = "0123456789ABCDEF";
	char		*start;

	start = dst;
	while (pow)
	{
		*dst++ = sym[ull / pow % base];
		pow /= base;
	}
	return (dst - start);
}

int	set_low_digits(int base,
	char *dst, unsigned long long ull, unsigned long long pow)
{
	static char	*sym = "0123456789abcdef";
	char		*start;

	start = dst;
	while (pow)
	{
		*dst++ = sym[ull / pow % base];
		pow /= base;
	}
	return (dst - start);
}
