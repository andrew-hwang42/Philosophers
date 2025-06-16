/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:20:52 by ahwang            #+#    #+#             */
/*   Updated: 2025/06/12 11:42:28 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	err_msg(char *msg)
{
	printf("Error: %s\n", msg);
}

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
		usleep(100);
}

void	free_data(t_data *data, char *msg)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->thread_philo[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&data->global_mutex_print);
	pthread_mutex_destroy(&data->global_mutex_state);
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	if (data->thread_philo)
		free(data->thread_philo);
	if (data->fork)
		free(data->fork);
	if (data->struct_philo)
		free(data->struct_philo);
	if (msg)
		err_msg(msg);
}
