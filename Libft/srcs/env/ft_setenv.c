/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:23:59 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/29 23:05:50 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>

char	**ft_getenvp(const char *name)
{
	extern char **environ;
	int			i;
	char		*end;

	i = 0;
	while (environ[i])
	{
		if ((end = ft_strchr(environ[i], '=')) == NULL)
			;
		else if (ft_strncmp(environ[i], name, end - environ[i]) == 0)
			return (environ + i);
		i++;
	}
	return (NULL);
}

int		t_setenv(const char *name, const char *value, int overwrite)
{
	char	**current;
	char	*str;

	current = ft_getenvp(name);
	if (current && overwrite == 0)
		return (-1);
	MCK(str = ft_strcjoin(name, '=', value), -1);
	if (current == NULL)
		return (ft_putenv(str));
	free(*current);
	return ((*current = str) != 0);
}
