# malloc
A malloc implementation

# API
```c
void  *malloc(size_t size);
void   free(void *ptr);
void   *realloc(void *ptr, size_t size);

void  show_alloc_mem(void);
```

# requirements

- Memory must be managed via `mmap(2)` and `mmunmap(2)`

- Pre-allocate 2 zones to satisfy at least 100 allocations:
  - small (1 to n bytes)
  - medium (n + 1 to m bytes)

If no free elements are found in the apropriate zone, the next is used.

- Large allocations are directly satisfied with `mmap`.

# architecture

- `malloc` is a first-fit algorithm

- `free` immediately coalleses neighboring free blocks

# implementation

Memory is managed with a doubly linked list. Free blocks have a `NULL` pointer as data.

```c
# define BLK_SZ sizeof(t_block)
# define IS_FREE(block) (block->data == NULL)
typedef struct  s_block
{
  struct s_block  *prev;
  struct s_block  *next;
  size_t          size;
  void            *data;
}               t_block;
```

We store pointers to the 3 zones.

```c
# define ZONE_S_SZ  16
# define ZONE_M_SZ  64

typedef struct  s_zones
{
  t_block *s;
  t_block *m;
  t_block *l;
}               t_zones;

t_zones *g_zones = { NULL, NULL, NULL };
```

We initialize the zones on the first call to `malloc`.

Implicitly moving from one zone to the next when iterating over the list woud be convenient. This way, if one zone is full, memory from the next is automatically allocated. Therefore, `zones` are adjacent heap addresses.

```c
//TODO: implement
```
Two search operations are defined over the list:

- To find a free block of at least a certain size

```c
t_block *get_zone(t_zones *zones, size_t size)
{
  if (size < ZONE_S_SZ)
    return (zones->s);
  if (size < ZONE_M_SZ)
    return (zones->m);
  return (zones->l);
}

t_block *get_free_block(t_zones zones, size_t size)
{
  t_block *block;
  
  block = get_zone(zones, size);
  while (block)
  {
    if (IS_FREE(block) && block->size >= size)
      return (block);
    block = block->next;
  }
  return (NULL);
}
```

- Finding an allocated block correstonding to an address. Since we dont know the allocated size, we iterate over all zones.

```c
t_block *find_block(t_zones zones, void* ptr)
{
  t_block *block;
  
  block = zones->s;
  while (block)
  {
    if (block->data == ptr)
      return (block);
    block = block->next;
  }
  return (NULL);
}
```
