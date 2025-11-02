#include "minirt.h"

void	init_arena(t_arena *arena, size_t size)
{
	arena->memory = malloc(size);
	arena->size = size;
	arena->used = 0;
}

void	*arena_add(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->used + size > arena->size)
		return (NULL); //TODO: cleanup and exit
	ptr = (char *)arena->memory + arena->used;
	arena->used += size;
	return (ptr);
}

void	delete_arena(t_arena *arena)
{
	free(arena->memory);
	arena->memory = NULL;
	arena->size = 0;
	arena->used = 0;
}