/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:29:58 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 12:06:49 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <unistd.h>

int		ft_putenv(char *str)
{
	extern char	**environ;
	char		**new_env;

	MCK(new_env = ft_strv_add(environ, str), -1);
	free(environ);
	environ = new_env;
	return (0);
}
