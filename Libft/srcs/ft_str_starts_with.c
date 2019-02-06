/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_starts_with.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:23:13 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/25 23:01:47 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_starts_with(const char *prefix, const char *str)
{
	char	*found;

	found = ft_strstr(str, prefix);
	if (found == str)
		return (found);
	return (NULL);
}
