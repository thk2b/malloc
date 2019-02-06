/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:46:42 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 00:48:19 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <stdlib.h>

typedef struct	s_llist_node
{
	struct s_llist_node	*next;
	void				*data;
}				t_llist_node;

typedef struct	s_llist
{
	t_llist_node	*first;
	t_llist_node	*last;
	size_t			len;
}				t_llist;

typedef void	(*t_llist_del_fn)(void *data);
typedef int		(*t_llist_cmp_fn)(void *ctx, void *data);

t_llist			*llist_new();
t_llist_node	*llist_new_node(void *data);
void			*llist_free(t_llist *head, t_llist_del_fn del);
int				llist_push(t_llist **head, void *data);
int				llist_pop(t_llist *head, void *data);
int				llist_shift(t_llist **head, void *data);
int				llist_unshift(t_llist *head, void *data);
t_llist_node	*llist_find(t_llist *head, void *ctx,
	t_llist_cmp_fn cmp);
int				llist_remove(t_llist *head, void *ctx,
	t_llist_cmp_fn cmp, t_llist_del_fn del);

#endif
