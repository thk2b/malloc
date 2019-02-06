/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_llist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 23:02:37 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 18:37:09 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"
#include "tests.h"
#include <assert.h>

static int	cmp(void *ctx, void *data)
{
	return (ft_strcmp(ctx, data) == 0);
}

int			g_delcount = 0;

static void	del(void *data)
{
	(void)data;
	g_delcount++;
}

static void	test0(void)
{
	t_llist			*head;
	char			**strv;
	t_llist_node	*found;

	head = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	llist_push(&head, strv[0]);
	llist_push(&head, strv[1]);
	llist_push(&head, strv[2]);
	assert(head->len == 3);
	assert(ft_strcmp(head->first->data, strv[0]) == 0);
	assert(ft_strcmp(head->first->next->data, strv[1]) == 0);
	assert(ft_strcmp(head->first->next->next->data, strv[2]) == 0);
	found = llist_find(head, "ghi", cmp);
	assert(ft_strcmp(found->data, "ghi") == 0);
	free(strv);
}

static void	test1(void)
{
	t_llist	*head;
	char	**strv;

	head = NULL;
	strv = ft_strsplit("abc def ghi jkl mno", ' ');
	llist_push(&head, strv[0]);
	llist_push(&head, strv[1]);
	llist_push(&head, strv[2]);
	llist_shift(&head, strv[3]);
	llist_shift(&head, strv[4]);
	assert(head->len == 5);
	assert(ft_strcmp((char*)head->first->data, strv[4]) == 0);
	assert(ft_strcmp(head->first->next->next->data,
		strv[0]) == 0);
	assert(ft_strcmp(head->first->next->next->next->next->data,
		strv[2]) == 0);
	llist_remove(head, "abc", cmp, del);
	assert(head->first->next->next->data == strv[1]);
	assert(g_delcount == 1);
	free(strv);
}

void		test_llist(void)
{
	test0();
	test1();
}
