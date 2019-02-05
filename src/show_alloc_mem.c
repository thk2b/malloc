/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:31:06 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:31:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

extern t_area_list	g_area_list;

void	show_alloc_mem(void)
{
	area_list__show_alloc_mem(&g_area_list);
}
