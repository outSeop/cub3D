#include <stdio.h>
#include "cub3D.h"
#include "libft/libft.h"
#include <unistd.h>


int main()
{
	t_game game;
	int fd = open("a.cub", O_RDONLY);

	init_game(&game);
	parsing_cub(&game.map, fd);
	for (int i = 0; i < 5; i++)
		printf("%s\n", game.map.textures[i]);
	printf("%X\n", game.map.floor);
	printf("%X\n", game.map.celling);
	int i;
	i=0;
	while (game.map.map[i])
	{
		printf("%s\n", game.map.map[i]);
		i++;
	}
}
