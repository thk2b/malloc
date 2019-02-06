/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:15:41 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 16:05:41 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include <stdlib.h>

typedef struct	s_stack
{
	void			*data;
	struct s_stack	*next;
}				t_stack;

typedef void	(*t_stack_del_fn)(void *data);
typedef int		(*t_stack_cmp_fn)(void *a, void *b);

t_stack			*stack_new_node(void *data);
void			stack_free(t_stack *s, t_stack_del_fn del);
int				stack_push(t_stack **s, void *data);
void			*stack_pop(t_stack **s);
int				stack_swap(t_stack *s);
int				stack_rotate(t_stack **s);
int				stack_rrotate(t_stack **s);
int				stack_is_sorted(t_stack *s, t_stack_cmp_fn fn);

#endif
