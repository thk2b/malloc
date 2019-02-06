/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:36:44 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 21:40:20 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t len)
{
	size_t	slen;
	char	*dup;

	slen = ft_strlen(s);
	len = slen < len ? slen : len;
	MCK(dup = (char*)malloc(sizeof(char) * (len + 1)), NULL);
	ft_strncpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
