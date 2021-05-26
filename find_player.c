#include "cub3D.h"

void			find_player(char *line, t_player *player, int num)
{
	int			i;
	int			j;

	i = 0;
	while (line[i])
	{
		if (!ft_strrchr(ALLOWED_TEXTS, line[i]))
			player->check = 999;
		j = 0;
		while (j < 4)
		{
			if (line[i] == ALL_DIRECTIONS[j])
			{
				set_player_dir_info(player, HX[j] - '0' - 2, HY[j] - '0' - 2);
				set_player_pos_info(player, i, num);
				player->check++;
				line[i] = '0';
				break ;
			}
			j++;
		}
		i++;
	}
}

int				save_map_info(char *line)
{
	int			i;
	int			res;
	int			int_colors[3];
	char		**colors;

	if (line[0] == '\0')
		print_error("ERROR - There is no Floor or ceiling info");
	colors = ft_split(line, ',');
	check_valid_color(colors);
	i = 0;
	while (i < 3)
	{
		int_colors[i] = ft_atoi(colors[i]);
		if (!(0 <= int_colors[i] && int_colors[i] <= 255))
			print_error("ERROR - out of color range");
		i++;
	}
	res = create_trgb(0, int_colors[0], int_colors[1], int_colors[2]);
	free_all(colors);
	return (res);
}

int				check_valid_color(char **colors)
{
	int			i;
	int			j;

	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				print_error("ERROR - Invalid argument in floor or celling\n");
			j++;
		}
		i++;
	}
	if (i != 3)
		print_error("ERROR - Lack of argument in floor or celling\n");
	return (1);
}
