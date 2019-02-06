/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strv_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:58:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 23:36:25 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strv_add(char **strv, char *str)
{
	size_t	len;
	char	**n;

	len = ft_strv_len(strv);
	if ((n = (char**)malloc(sizeof(char*) * (len + 2))) == NULL)
		return (NULL);
	ft_memcpy(n, strv, (len + 1) * (sizeof(char*)));
	n[len] = str;
	n[len + 1] = NULL;
	return (n);
}
