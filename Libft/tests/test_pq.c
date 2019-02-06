/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:36:39 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 09:30:05 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "tests.h"
#include "libft.h"
#include <assert.h>

static void	del(void *data)
{
	free(data);
}

static void	test0(void)
{
	char	**strv;
	t_pq	*pq;

	pq = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	pq_add(&pq, strv[0], 0, 0);
	pq_add(&pq, strv[1], 2, 0);
	pq_add(&pq, strv[2], 1, 0);
	pq_add(&pq, strv[3], 3, 0);
	assert(pq_pop(&pq, del) == strv[3]);
	assert(pq_get(pq) == strv[1]);
	assert(pq_pop(&pq, del) == strv[1]);
	assert(pq_get(pq) == strv[2]);
	assert(pq_pop(&pq, del) == strv[2]);
	assert(pq_pop(&pq, del) == strv[0]);
	assert(pq_pop(&pq, del) == NULL);
	pq_free(pq, del);
	free(strv);
}

static void	test1(void)
{
	char	**strv;
	t_pq	*pq;

	pq = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	pq_add(&pq, strv[3], 3, 1);
	pq_add(&pq, strv[0], 0, 1);
	pq_add(&pq, strv[1], 2, 1);
	pq_add(&pq, strv[2], 1, 1);
	assert(pq_pop(&pq, del) == strv[0]);
	assert(pq_get(pq) == strv[2]);
	assert(pq_pop(&pq, del) == strv[2]);
	assert(pq_get(pq) == strv[1]);
	assert(pq_pop(&pq, del) == strv[1]);
	assert(pq_pop(&pq, del) == strv[3]);
	assert(pq_pop(&pq, del) == NULL);
	pq_free(pq, del);
	free(strv);
}

static void	test2(void)
{
	char	**strv;
	t_pq	*pq;

	pq = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	pq_add(&pq, strv[0], 0, 1);
	pq_add(&pq, strv[1], 0, 1);
	pq_add(&pq, strv[2], 0, 1);
	pq_add(&pq, strv[3], 0, 1);
	assert(pq_pop(&pq, del) == strv[0]);
	assert(pq_get(pq) == strv[1]);
	assert(pq_pop(&pq, del) == strv[1]);
	assert(pq_get(pq) == strv[2]);
	assert(pq_pop(&pq, del) == strv[2]);
	assert(pq_pop(&pq, del) == strv[3]);
	assert(pq_pop(&pq, del) == NULL);
	pq_free(pq, del);
	free(strv);
}

void		test_pq(void)
{
	test0();
	test1();
	test2();
}
