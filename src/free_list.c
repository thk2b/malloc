#include <malloc.h>

void	free_list_insert(t_fblock *fblock)
{
	extern t_free_list	g_free_lists[];
	t_free_list			*free_list;
	t_fblock			*cur;

	free_list = g_free_lists + free_list_index(fblock->block.size);
	cur = free_list->head;
	while (cur && (void*)fblock < (void*)cur)
		cur = cur->next;
	free_list_insert_after(cur, fblock);
}

void	free_list_insert_after(t_fblock *prev, t_fblock *fblock)
{
	extern t_free_list	g_free_lists[];
	t_fblock			*next;

	if (prev == NULL)
	{
		fblock->prev = NULL;
		fblock->next = NULL;
		g_free_lists[free_list_index(fblock->block.size)].head = fblock;
		return ;
	}
	next = prev->next;
	prev->next = fblock;
	if (next)
		next->prev = fblock;
	fblock->next = next;
	fblock->prev = prev;
}

void	free_list_remove(t_fblock *fblock)
{
	extern t_free_list	g_free_lists[];

	if (fblock->prev == NULL)
		g_free_lists[free_list_index(fblock->block.size)].head = fblock->next;
	else
		fblock->prev->next = fblock->next;
	if (fblock->next)
		fblock->next->prev = fblock->prev;
	fblock->next = NULL;//TODO: remove me
	fblock->prev = NULL;
}
