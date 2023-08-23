/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:52:06 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/24 15:25:40 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	int		atoi;
	char	*itoa;

	atoi = ft_atoi(str);
	itoa = ft_itoa(atoi);
	if (!ft_strcmp(itoa, str))
		return (free(itoa), 1);
	else
		return (free(itoa), 0);
}
