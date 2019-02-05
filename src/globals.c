/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:13:14 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:13:16 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <free_list.h>
#include <area_list.h>

t_area_list	g_area_list = {
	NULL, NULL
};

t_free_list	g_free_lists[FL__N_FREE_LISTS] = {
	{NULL, 0, 0},
	{NULL, 256, 1},
	{NULL, 1024, 2}
};

int			g_log_fd;
