/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:39:23 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 20:21:18 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	death_checker(t_data *data, int i, size_t now)
{
	int	status;

	status = 1;
	if (now - data->struct_philo[i].time_last >= (size_t)data->time_to_die)
	{
		if (pthread_mutex_lock(&data->global_mutex_state))
		{
			err_msg("failed to lock mutex");
			status = 0;
		}
		else
		{
			if (data->state != FULL)
				data->state = DEAD;
			if (data->state == DEAD && !philo_print_die(&data->struct_philo[i]))
				status = 0;
			if (pthread_mutex_unlock(&data->global_mutex_state))
			{
				pthread_mutex_unlock(&data->struct_philo[i].thread_mutex);
				return (err_msg("failed to unlock mutex"), 0);
			}
		}
		status = 0;
	}
	return (status);
}

int	check_each_philo(t_data *data, int i)
{
	int		status;

	if (data->struct_philo[i].finished)
		return (1);
	if (pthread_mutex_lock(&data->struct_philo[i].thread_mutex))
		return (err_msg("failed to lock mutex"), 0);
	status = death_checker(data, i, get_time_mili());
	if (pthread_mutex_unlock(&data->struct_philo[i].thread_mutex))
		return (err_msg("failed to unlock mutex"), 0);
	return (status);
}

int	monitoring(t_data *data)
{
	int	i;

	if (data->num_of_philo == 1)
		return (1);
	i = 0;
	while (1)
	{
		if (get_state(&data->struct_philo[i]) == FULL)
			return (1);
		if (!check_each_philo(data, i))
			return (0);
		i++;
		if (i == data->num_of_philo)
			i = 0;
	}
	return (1);
}
