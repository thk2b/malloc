# Algorithm

## Application

### Malloc

```
malloc(size)
	block, area := Block.find_free(size)
	if block is null
		block, area := Block.new(size)
	if block is null
		return null # No memory
	block.allocate(area)
	return block.data
```

### Free

```
free(address)
	block, area := Block.find(address, area)
	if block is null
		exit(1) # Not allocated
	block.deallocate(area)
```

### Realloc

```
realloc(address, size)
	block, area := Block.find(address)
	if block is null
		exit(1) # Not allocated
	extended_block := block.extend(size, area)
	if extended_block is null
		new_block := malloc(size)
		copy(new_block.data, address, block->size)
		free(block)
		return new_block.data
	return extended_block.data
```

### Display

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

## Modules

### Searches

Bool			first_fit(FBlock, Area, target_size)
Fblock			best_fit(Fblock, Area, target_size, Fblock)
Bool			match_address(Block, Area, address)

### Block

Block, Area		Block.find(address)
				Block.deallocate(area)
FBlock, Area	FBlock.find_free(size)
				FBlock.allocate(area)
size			Fblock.lookback(target_size)
size			Fblock.lookahead(target_size)
FBlock			FBlock.extend(target_size)
Fblock, Fblock	Fblock.split(target_size)
				Fblock.print(fd)
				Block.print(fd)
				Block.log(msg)

### AreaList

				AreaList.request_memory() // AreaList.extend()
Area			AreaList.find(address)
AreaList		AreaList.append(Area)
AreaList		AreaList.shift(Area)
				Area.log(msg)

### Area

Block			Area.search(fn, ctx)
Block			Area.search_back(fn, ctx)
Bool			Area.in_bounds(Block)
Bool			Area.is_first(Block)
Bool			Area.is_last(Block)
Bool			Area.can_fit(size)
				Area.print(fd)
				Area.log(msg)

### FreeList

FreeList		FreeList.find(size)
Fblock			FreeList.search(fn, ctx)
Fblock			FreeList.reduce(fn, ctx)
				FreeList.insert(Fblock)
				FreeList.insertAfter(Fblock)
				FreeList.remove(Fblock)
				FreeList.removeRange(Fblock, Fblock)
