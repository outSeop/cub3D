#include <stdio.h>
#include "cub3D.h"
#include "libft/libft.h"
#include <unistd.h>


int main()
{
	t_map map;
	int fd = open("a.cub", O_RDONLY);

	parsing_map(&map, fd);
	for (int i = 0; i < 5; i++)
		printf("%s\n", map.textures[i]);
	printf("%X\n", map.celling);
	printf("%X\n", map.floor);
	while (1)
	{}

}
