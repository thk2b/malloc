/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:07:25 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:07:26 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <shared.h>
#include <string.h>
#include <libft.h>

void	*calloc(size_t count, size_t size)
{
	void	*addr;
	size_t	total;

	total = size * count;
	addr = malloc(size);
	if (addr)
		ft_bzero(addr, size);
	return (addr);
}
