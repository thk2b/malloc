/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 22:11:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 11:49:18 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strvdel(char **strv)
{
	size_t	len;
	size_t	i;

	len = ft_strv_len(strv);
	i = 0;
	while (i < len)
	{
		free(strv[i]);
		i++;
	}
	free(strv);
	strv = NULL;
}
