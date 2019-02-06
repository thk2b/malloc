/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 00:44:57 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 01:23:27 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int		ft_atoi_validate(int *error, const char *s)
{
	int		sign;
	long	new_n;
	long	n;

	sign = 1;
	n = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n'
		|| *s == '\v' || *s == '\r' || *s == '\f')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return ((*error = 1));
		if ((new_n = 10 * n + *s++ - '0') >= n && new_n <= INT_MAX)
			n = new_n;
		else
			return ((*error = 1));
	}
	*error = 0;
	return ((int)(n * sign));
}
