#include <stdio.h>
#include "libft/libft.h"

int				find_space(char c)
{
	if (('\r' < c && c < '\t') || c == ' ')
		return (1);
	return (0);
}

char		*save_path(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		if (find_space(line[i]))
			i++;
		else
			break;

	return (ft_strdup(line));
}

int main()
{
	char	*arr = "a 678";
	char	*str;
	str = save_path(arr + 1);
	printf("%s\n", str);

}
