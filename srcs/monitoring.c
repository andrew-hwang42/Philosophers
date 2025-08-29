/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:39:23 by ahwang            #+#    #+#             */
/*   Updated: 2025/08/29 06:49:36 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_each_philo(t_data *data, int i)
{
	if (data->time_to_die < data->time_to_eat + data->time_to_sleep)
		custom_usleep(1);
	else
		custom_usleep(100);
	if (pthread_mutex_lock(&data->struct_philo[i].thread_mutex))
		return (err_msg("failed to lock mutex"), 0);
	if (get_time_mili() - data->struct_philo[i].time_last
		>= (size_t)data->time_to_die)
	{
		if (pthread_mutex_lock(&data->global_mutex_state))
			return (err_msg("failed to lock mutex"), 0);
		if (data->state != FULL)
			data->state = DEAD;
		if (data->state != FULL || data->state == DEAD)
		{
			if (!philo_print(&data->struct_philo[i], "died"))
				return (0);
		}
		if (pthread_mutex_unlock(&data->global_mutex_state))
			return (err_msg("failed to unlock mutex"), 0);
		return (0);
	}
	if (pthread_mutex_unlock(&data->struct_philo[i].thread_mutex))
		return (err_msg("failed to unlock mutex"), 0);
	return (1);
}

int	monitoring(t_data *data)
{
	int	i;

	if (data->num_of_philo == 1)
		return (1);
	i = 0;
	while (1)
	{
		if (!check_each_philo(data, i))
			return (0);
		i++;
		if (i == data->num_of_philo)
			i = 0;
	}
	return (1);
}
