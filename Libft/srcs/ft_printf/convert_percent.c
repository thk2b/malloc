/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:58:25 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 15:37:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "libft.h"
#include <stdlib.h>

int	convert_percent(char **dst, t_directive *d)
{
	t_convertion_len	len;
	size_t				cur;

	cur = 0;
	get_len(&len, d, 1, 0);
	if ((*dst = (char*)malloc(sizeof(char) * len.total)) == NULL)
		return (-1);
	cur += set_pre(*dst, &len, d, 0);
	ft_strcpy(*dst + cur++, "%");
	cur += set_post(*dst + cur, &len, d);
	return (cur);
}
