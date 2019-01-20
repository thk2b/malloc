#include <shared.h>
#include <assert.h>
#include <string.h>

static inline t_block	*do_coalesce(t_area *a, t_block *b, size_t requested_size)
{
	size_t			total;
	t_block			*cur;
	void			*end;

	end = AREA__CUR_END(a);
	total = 0;
	cur = b;
	while ((void*)cur < end && total < requested_size)
	{
		total += cur->size + sizeof(t_block);
		if (cur->free)
			area__destroy_free_block(a, (t_free_block*)cur);
		cur = BLOCK__NEXT(cur);
	}
	if ((void*)cur == end && total < requested_size)
	{
		a->cur_size += requested_size - total;
		total = requested_size;
	}
	assert(total >= requested_size);
	b->size = total - sizeof(t_block);
	#ifdef LOG
	block__log(b, "coalessed");
	#endif
	return (b);
}

static inline t_block	*do_coalesce_back(t_area *a, t_block *b, size_t offset, size_t requested_size)
{
	t_block	*new_block;

	assert(AREA__IS_IN_BOUNDS(a, (char*)b - offset));
	new_block = (t_block*)((char*)b - offset);
	new_block->free = 0;
	memcpy(BLOCK__DATA(new_block), BLOCK__DATA(b), MIN(b->size, requested_size));
	return (do_coalesce(a, new_block, requested_size));
}

t_block						*area__coalesce_block(t_area *a, t_block *b, size_t requested_size)
{
	size_t			space_before;
	size_t			space_after;
	size_t			total_size;

	space_after = area__count_free_space_after(a, b, requested_size, NULL);
	space_before = 0;
	total_size = space_after + sizeof(t_block) + b->size; 
	if (total_size < requested_size)
		space_before = area__count_free_space_before(a, b, requested_size);
	total_size += space_before;
	if (total_size < requested_size)
		return (NULL);
	if (space_before)
		b = do_coalesce_back(a, b, space_before, requested_size);
	else
		b = do_coalesce(a, b, requested_size);
	if (b->size > requested_size)
		area__split_block(a, b, requested_size);
	return (b);
}
