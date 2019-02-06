/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 12:47:56 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 13:10:46 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "tests.h"
#include "libft.h"
#include <assert.h>

static void	test0(void)
{
	t_queue	*q;
	char	**strv;

	q = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	queue_add(&q, strv[0]);
	queue_add(&q, strv[1]);
	queue_add(&q, strv[2]);
	queue_add(&q, strv[3]);
	queue_add(&q, strv[4]);
	assert(queue_pop(q) == strv[0]);
	assert(queue_pop(q) == strv[1]);
	assert(queue_pop(q) == strv[2]);
	queue_add(&q, strv[0]);
	assert(queue_pop(q) == strv[3]);
	assert(queue_pop(q) == strv[4]);
	assert(queue_pop(q) == strv[0]);
	assert(queue_pop(q) == NULL);
}

void		test_queue(void)
{
	test0();
}
