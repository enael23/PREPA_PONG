/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:28:05 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 16:17:11 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	name_file(char *str)
{
	int	i;

	i = ft_strlen(str) - 4;
	if (i <= 0 || ((str[i] && str[i] != '.')
			|| (str[i + 1] && str[i + 1] != 'c')
			|| (str[i + 2] && str[i + 2] != 'u')
			|| (str[i + 3] && str[i + 3] != 'b')))
		return (1);
	return (0);
}

int	parsing(char *map, t_va *va)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (1);
	ret = 0;
	while (get_next_line(&line, fd))
	{
		if (line[0] == 'N' && line[1] && line[1] == 'O')
			ret += get_strtxt(line, 0, va);
		if (line[0] == 'S' && line[1] && line[1] == 'O')
			ret += get_strtxt(line, 1, va);
		if (line[0] == 'W' && line[1] && line[1] == 'E')
			ret += get_strtxt(line, 2, va);
		if (line[0] == 'E' && line[1] && line[1] == 'A')
			ret += get_strtxt(line, 3, va);
		if (line[0] == 'F' || line[0] == 'C')
			ret += get_colors(line, va);
		if (is_map(line))
			ret += parse_map(line, fd, va);
		free(line);
	}
	return (free(line), ret);
}
