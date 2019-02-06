/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:19:17 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 15:40:22 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <limits.h>

int	ft_snprintf(char *s, size_t len, const char *fmt, ...)
{
	va_list	ap;
	int		real_len;
	char	*tmp;

	va_start(ap, fmt);
	real_len = ft_vasprintf(&tmp, fmt, ap);
	if (s == NULL && len == 0)
		return (real_len);
	tmp[len] = '\0';
	ft_strncpy(s, tmp, len - 1);
	va_end(ap);
	free(tmp);
	return (real_len);
}

int	ft_sprintf(char *s, const char *fmt, ...)
{
	va_list	ap;
	int		real_len;
	char	*tmp;

	va_start(ap, fmt);
	real_len = ft_vasprintf(&tmp, fmt, ap);
	ft_strcpy(s, tmp);
	va_end(ap);
	free(tmp);
	return (real_len);
}
