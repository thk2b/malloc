#include <ft_malloc.h>
#include <assert.h>
#include <stdlib.h>

void	block_flags(void)
{
	t_area	*area;
	t_block	*block;

	if ((area = new_area(0)) == NULL)
		exit(1);
	block = A_HEAD(area);
	new_block(block, 160, NULL);
	assert(B_SIZE(block) == 160);
	assert(B_IS_USED(block) > 0);
	assert(B_IS_FREE(block) == 0);
	B_SET_FREE(block);
	assert(B_IS_USED(block) == 0);
	assert(B_IS_FREE(block) > 0);
	B_SET_USED(block);
	assert(B_IS_USED(block) > 0);
	assert(B_IS_FREE(block) == 0);
	B_SET_SIZE(block, 1024);
	assert(B_SIZE(block) == 1024);
	B_SET_SIZE(block, 1024000);
	assert(B_SIZE(block) == 1024000);
}

int		main(void)
{
	block_flags();
}
