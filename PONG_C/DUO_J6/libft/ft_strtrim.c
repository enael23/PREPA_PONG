/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:31:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 16:10:48 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_startstring(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			if (s1[i] == 0)
				return (0);
			j = -1;
		}
		j++;
	}
	return (i);
}

size_t	ft_endstring(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	if (s1[0] == 0)
		return (0);
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i--;
			if (i == 0)
				return (0);
			j = -1;
		}
		j++;
	}
	return (i + 1);
}

int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	if (!is_in_set(s1[0], set) && !is_in_set(s1[ft_strlen(s1) - 1], set))
		return (ft_strdup(s1));
	start = ft_startstring(s1, set);
	end = ft_endstring(s1, set);
	i = 0;
	cpy = malloc(sizeof(char) * (end - start) + 1);
	if (!cpy)
		return (NULL);
	if (start == end)
	{
		cpy[i] = 0;
		return (cpy);
	}
	while (start < end)
		cpy[i++] = s1[start++];
	cpy[i] = 0;
	return (cpy);
}
