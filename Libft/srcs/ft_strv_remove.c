/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strv_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 23:26:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 11:13:42 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strv_remove(char **strv, size_t index)
{
	char	**n;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strv_len((char **)strv);
	if ((n = (char**)malloc(sizeof(char*) * (len - 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != index)
			n[j++] = strv[i++];
		else
			i++;
	}
	n[len - 1] = NULL;
	return (n);
}
