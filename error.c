#include "cub3D.h"

int			error_input(int argc, char *argv[])
{
	int		fd;
	char 	*str;

	if (argc != 2)
		return (print_error("input error"));
	str = ft_strrchr(argv[1], '.');
	if (ft_strlen(str) != 4)
		return (print_error("input error"));
	if (ft_strncmp(str, ".cub", 4))
		return (print_error("input error"));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("input eeror"));
	return (fd);
}

int			error_file(t_map *map)
{
	int		fd;
	int		i;

	i = 0;
	while (i < 5)
	{
		fd = open(map->textures[i], O_RDONLY) ;
		if (fd == -1)
		{
			print_error("file error");
			while (1)
			{}
			return (-1);
		}
		i++;
	}
return (1);
}

int		print_error(char *error)
{
	printf("%s\n", error);
	return (-1);
}
