#include "cub3D.h"

int				error_input(int argc, char *argv[], int *sc)
{
	int			fd;
	char		*str;

	if (!(argc >= 2 && argc <= 3))
		return (print_error("input error"));
	if (argc == 3)
		*sc = check_sc(argv[2]);
	str = ft_strrchr(argv[1], '.');
	if (ft_strlen(str) != 4)
		return (print_error("input error"));
	if (ft_strncmp(str, ".cub", 4))
		return (print_error("input error"));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("input eeror"));
	return (fd);
}

int				error_file(t_map *map)
{
	int			fd;
	int			i;

	i = 0;
	while (i < 5)
	{
		fd = open(map->textures[i], O_RDONLY);
		if (fd == -1)
		{
			print_error("file error");
			return (0);
		}
		i++;
	}
	return (1);
}

int				print_error(char *error)
{
	printf("%s\n", error);
	exit(-1);
	return (-1);
}

int				check_sc(char *argv)
{
	int			len;

	len = ft_strlen(argv);
	if (len != 6)
		return (0);
	if (!(ft_strncmp(argv, "--save", 6)))
		return (1);
	return (0);
}
