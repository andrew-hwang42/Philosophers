/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:54:19 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 19:56:50 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

size_t	get_time_mili(void)
{
	struct timeval	current;
	size_t			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000;
	time += current.tv_usec / 1000;
	return (time);
}

size_t	get_time_micro(void)
{
	struct timeval	current;
	size_t			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec;
	time *= 1000000;
	time += current.tv_usec;
	return (time);
}

void	custom_usleep(size_t timecheck)
{
	size_t	start;

	start = get_time_micro();
	timecheck *= 1000;
	while (get_time_micro() - start < timecheck)
		usleep(500);
}

void	custom_usleep_philo(t_philo *philo, size_t timecheck)
{
	size_t	start;

	start = get_time_micro();
	timecheck *= 1000;
	while (get_time_micro() - start < timecheck)
	{
		if (get_state(philo) == DEAD)
			break ;
		usleep(500);
	}
}
