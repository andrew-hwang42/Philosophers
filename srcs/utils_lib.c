/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:13:27 by ahwang            #+#    #+#             */
/*   Updated: 2025/06/10 12:35:10 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_modified_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (err_msg("invalid character exists"), 0);
		nbr = nbr * 10 + (*str - '0');
		i++;
	}
	if (ft_strlen(str) > ft_strlen("2147483647")
		|| nbr > 2147483647)
		return (err_msg("out of int range"), 0);
	return (nbr);
}
