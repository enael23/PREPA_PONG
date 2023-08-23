/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:22:07 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 16:16:19 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**trim_all(char **split)
{
	char	**new;
	int		i;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (write(2, "Failed malloc\n", 14), NULL);
	new[i] = NULL;
	while (--i >= 0)
		new[i] = ft_strtrim(split[i], " ");
	ft_freesplit(split);
	return (new);
}

int	get_strtxt(char *line, int num, t_va *va)
{
	int	i;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	va->strtxt[num] = ft_strdup(&line[i]);
	return (0);
}

void	get_colors2(char *line, t_va *va, char **split)
{
	if (line[0] == 'F')
	{
		va->fcolor = ft_atoi(split[0]) << 16
			| ft_atoi(split[1]) << 8 | ft_atoi(split[2]);
		va->fcolor_status = 1;
	}
	if (line[0] == 'C')
	{
		va->ccolor = ft_atoi(split[0]) << 16
			| ft_atoi(split[1]) << 8 | ft_atoi(split[2]);
		va->ccolor_status = 1;
	}
}

int	get_colors(char *line, t_va *va)
{
	int		i;
	char	**split;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	split = ft_split(&line[i], ',');
	split = trim_all(split);
	if (!split)
		return (write(2, "Failed malloc\n", 14), 1);
	i = -1;
	while (split[++i])
		if (!ft_isint(split[i])
			|| (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255))
			return (ft_freesplit(split), 1);
	if (i != 3)
		return (ft_freesplit(split), 1);
	if (line[0] == 'F' || line[0] == 'C')
		get_colors2(line, va, split);
	ft_freesplit(split);
	return (0);
}
