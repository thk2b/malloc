/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:14:44 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 13:25:20 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#include "libft.h"

int	main(void)
{
	ft_putendl("llist");
	test_llist();
	ft_putendl("hm");
	test_hm();
	ft_putendl("queue");
	test_queue();
	ft_putendl("pq");
	test_pq();
}
