/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:24:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 12:52:49 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_orient(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	get_player(t_va *va)
{
	int	i;
	int	j;

	i = -1;
	while (va->map[++i])
	{
		j = -1;
		while (va->map[i][++j])
			if (is_orient(va->map[i][j]))
				break ;
		if (va->map[i][j])
			break ;
	}
	if (va->map[i][j] == 'N')
		va->pa = 3 * PI / 2;
	else if (va->map[i][j] == 'E')
		va->pa = 0;
	else if (va->map[i][j] == 'S')
		va->pa = PI / 2;
	else
		va->pa = PI;
	va->map[i][j] = '0';
	va->px = j + 0.5;
	va->py = i + 0.5;
	return (0);
}

int	check_mapchars(char *mapstr)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (mapstr[i])
	{
		if (mapstr[i] != ' ' && mapstr[i] != '0' && mapstr[i] != '1'
			&& mapstr[i] != 'N' && mapstr[i] != 'S' && mapstr[i] != 'E'
			&& mapstr[i] != 'W' && mapstr[i] != '\n')
			return (1);
		if (mapstr[i] == 'N' || mapstr[i] == 'S'
			|| mapstr[i] == 'E' || mapstr[i] == 'W')
			pos++;
		i++;
	}
	if (pos != 1)
		return (1);
	return (0);
}

int	parse_map(char *line, int fd, t_va *va)
{
	char	*mapstr;
	char	*line2;

	mapstr = ft_strdup(line);
	if (!mapstr)
		return (write(2, "Failed malloc\n", 14), 1);
	while (get_next_line(&line2, fd))
	{
		if (isempty_line(line2))
			return (free(line2), free(mapstr), 1);
		mapstr = ft_strcatf(mapstr, "\n", 1);
		mapstr = ft_strcatf(mapstr, line2, 3);
	}
	if (line2)
		free(line2);
	if (check_mapchars(mapstr))
		return (free(mapstr), 1);
	va->map = ft_split(mapstr, '\n');
	if (!va->map)
		return (write(2, "Failed malloc\n", 14), free(mapstr), 1);
	free(mapstr);
	if (get_rectangle(va) || get_player(va) || check_map(va->map))
		return (1);
	return (0);
}
