/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:25:36 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/18 17:26:28 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map(char *line)
{
	int	i;
	int	one;

	one = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			one = 1;
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		i++;
	}
	if (one == 0)
		return (0);
	return (1);
}

int	isempty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

char	*dup_withspaces(char *str, int size)
{
	char	*new;
	int		i;

	new = alloc_with(size, ' ');
	if (!new)
		return (write(2, "Failed malloc\n", 14), NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}

int	get_rectangle(t_va *va)
{
	char	**newmap;
	int		size;
	int		i;

	size = 0;
	i = -1;
	while (va->map[++i])
		if (size < (int)ft_strlen(va->map[i]))
			size = (int)ft_strlen(va->map[i]);
	newmap = (char **)malloc(sizeof(char *) * (i + 1));
	if (!newmap)
		return (1);
	newmap[i] = NULL;
	while (--i >= 0)
	{
		if ((int)ft_strlen(va->map[i]) == size)
			newmap[i] = ft_strdup(va->map[i]);
		else
			newmap[i] = dup_withspaces(va->map[i], size);
		if (!newmap[i])
			return (ft_freesplit(newmap), 1);
	}
	ft_freesplit(va->map);
	va->map = newmap;
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
				if (!map[i - 1][j - 1] || map[i - 1][j - 1] == ' '
					|| !map[i - 1][j] || map[i - 1][j] == ' '
					|| !map[i - 1][j + 1] || map[i - 1][j + 1] == ' '
					|| !map[i][j - 1] || map[i][j - 1] == ' '
					|| !map[i][j + 1] || map[i][j + 1] == ' '
					|| !map[i + 1][j - 1] || map[i + 1][j - 1] == ' '
					|| !map[i + 1][j] || map[i + 1][j] == ' '
					|| !map[i + 1][j + 1] || map[i + 1][j + 1] == ' ')
					return (1);
		}
	}
	return (0);
}
