/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:21:17 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/29 22:21:03 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <unistd.h>

char		*ft_getenv(const char *name)
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
			return (end + 1);
		i++;
	}
	return (NULL);
}
