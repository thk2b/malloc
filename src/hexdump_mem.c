/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:13:21 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:13:21 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

extern t_area_list	g_area_list;

void	hexdump_mem(void)
{
	int	fd;

	fd = 1;
	area_list__foreach(&g_area_list, area__hexdump, &fd);
	hexdump(NULL, 0, NULL);
	put_str(1, "\n");
}
