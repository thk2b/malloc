/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 00:28:08 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 21:59:23 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"
#include "libft.h"
#include <assert.h>

static void	test0(void)
{
	t_hm	*hm;
	char	**strv;

	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	hm = hm_new(1, NULL);
	hm_insert(hm, "1", strv[0]);
	hm_insert(hm, "2", strv[1]);
	hm_insert(hm, "3", strv[2]);
	hm_insert(hm, "4", strv[3]);
	assert(hm_find(hm, "1") == strv[0]);
	assert(hm_find(hm, "4") == strv[3]);
}

static void	test1(void)
{
	t_hm	*hm;
	char	**strv;

	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	hm = hm_new(3, NULL);
	hm_insert(hm, "123", strv[0]);
	hm_insert(hm, "223", strv[1]);
	hm_insert(hm, "3345", strv[2]);
	hm_insert(hm, "463543", strv[3]);
	assert(hm_find(hm, "123") == strv[0]);
	assert(hm_find(hm, "") == NULL);
	assert(hm_find(hm, "3345") == strv[2]);
	hm_remove(hm, "223");
	assert(hm_find(hm, "223") == NULL);
}

void		test_hm(void)
{
	test0();
	test1();
}
