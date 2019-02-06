/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:35:40 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/10 16:18:22 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_buffer.h"
#include "libft.h"
#include <stdlib.h>

static t_lbuf_head	*lbuf_new_head(void)
{
	t_lbuf_head *h;

	if ((h = (t_lbuf_head*)malloc(sizeof(t_lbuf_head))) == NULL)
		return (NULL);
	h->data = NULL;
	h->last = NULL;
	h->total_len = 0;
	return (h);
}

static t_lbuf_block	*lbuf_new_block(char *data, size_t len)
{
	t_lbuf_block *b;

	if ((b = (t_lbuf_block*)malloc(sizeof(t_lbuf_block))) == NULL)
		return (NULL);
	b->len = len;
	b->data = data;
	b->next = NULL;
	return (b);
}

void				lbuf_add(t_lbuf_head **head, char *data, size_t len)
{
	t_lbuf_block *block;

	if (*head == NULL && (*head = lbuf_new_head()) == NULL)
		return ((void)NULL);
	if ((block = lbuf_new_block(data, len)) == NULL)
		return ((void)NULL);
	if ((*head)->data == NULL)
		(*head)->data = block;
	else
		(*head)->last->next = block;
	(*head)->last = block;
	(*head)->total_len += len;
}

static void			join_blocks(t_lbuf_block *block, char **cur, size_t *len)
{
	size_t			cur_len;

	while (block)
	{
		if ((cur_len = MIN(block->len, *len)))
		{
			ft_memcpy(*cur, block->data, cur_len);
			*len -= cur_len;
			*cur += cur_len;
		}
		free(block->data);
		free(block);
		block = block->next;
	}
}

char				*lbuf_join(t_lbuf_head *head)
{
	size_t			len;
	char			*str;
	char			*cur;
	t_lbuf_block	*block;

	if (head == NULL)
		return (ft_strdup(""));
	len = head->total_len;
	if ((str = malloc((sizeof(char) * (1 + len)))) == NULL)
		return (NULL);
	block = head->data;
	cur = str;
	join_blocks(block, &cur, &len);
	*cur = '\0';
	return (str);
}
