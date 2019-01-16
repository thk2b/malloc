#include <malloc.h>
#include <assert.h>

void	free_list_insert(t_fblock *fblock, t_area *area)
{
	extern t_free_list	g_free_lists[];
	t_free_list			*free_list;
	t_fblock			*cur;
	t_fblock			*prev;

	free_list = g_free_lists + free_list_index(fblock->block.size);
	cur = free_list->head;
	prev = NULL;
	while (cur && (void*)fblock > (void*)cur)
	{
		prev = cur;
		cur = cur->next;
	}
	assert(prev < fblock);
	free_list_insert_after(prev, fblock, area);
}

static inline void	set_next_block_prev_block_free(t_fblock *fblock, t_area *area, int value)
{
	void	*area_end;
	t_block	*next;

	area_end = AREA_CUR_END(area);
	next = BLOCK_NEXT((t_block*)fblock);
	if ((void*)next < area_end)
	{
		assert(next->prev_free != value);
		next->prev_free = value;
	}
}

void	free_list_insert_after(t_fblock *prev, t_fblock *fblock, t_area *area)
{
	extern t_free_list	g_free_lists[];
	t_fblock			*next;

	if (BLOCK_NEXT((t_block*)fblock) == AREA_CUR_END(area))
	{
		area->cur_size -= (fblock->block.size + sizeof(t_area));
		malloc_log((t_block*)fblock, "removed wilderness block");
		return ;
	}
	set_next_block_prev_block_free(fblock, area, 1);
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
	assert((void*)fblock->prev < (void*)fblock);
	assert(fblock->next == NULL || (void*)fblock->next > (void*)fblock);
}

void	free_list_remove(t_fblock *fblock, t_area *area)
{
	extern t_free_list	g_free_lists[];

	set_next_block_prev_block_free(fblock, area, 1);
	if (fblock->prev == NULL)
		g_free_lists[free_list_index(fblock->block.size)].head = fblock->next;
	else
		fblock->prev->next = fblock->next;
	if (fblock->next)
		fblock->next->prev = fblock->prev;
	fblock->next = NULL;//TODO: remove me
	fblock->prev = NULL;
}
