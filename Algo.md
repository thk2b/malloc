# Algorithm

## Malloc

```
malloc(size)
	block := Block.find_free(size)
	if block is null
		block := Block.new(size)
	if block is null
		return null # No memory
	block.allocate()
	return block.data
```

## Free

```
free(address)
	block := Block.find(address)
	if block is null
		exit(1) # Not allocated
	block.deallocate()
```

## Realloc

```
realloc(address, size)
	block := Block.find(address)
	if block is null
		exit(1) # Not allocated
	extended_block := block.extend(size)
	if extended_block is null
		new_block := malloc(size)
		copy(new_block.data, address, block->size)
		free(block)
		return new_block.data
	return extended_block.data
```

## Display

```
show_alloc_mem()
	total := 0, 0
	area := global.area
	while area
		area.print()
		total += area->cur_size, area->size
		block := area.head
		while block
			block.print()
			block := block.next
	total.print()
```

```
hexdump_mem()
	while area
		area.hexdump()
		block := area.head
		while block
			block.hexdump()
			block := block.next
```
