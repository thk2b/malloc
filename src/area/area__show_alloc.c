#include <shared.h>

void	area__show_alloc(t_area *area, void *ctx)
{
	UNUSED(ctx);
	put_str(1, "Area\n");
	area__foreach(area, block__show_alloc, NULL);
	put_dec(1, area->cur_size);
	put_str(1, "/");
	put_dec(1, area->size);
	put_str(1, " bytes\n");
}
