/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:22:27 by ahwang            #+#    #+#             */
/*   Updated: 2025/08/29 06:44:59 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	init_struct_philo(t_data *data, int i)
{
	memset(&data->struct_philo[i], 0, sizeof(t_philo));
	data->struct_philo[i].id = i + 1;
	data->struct_philo[i].left_fork = &data->fork[i];
	data->struct_philo[i].right_fork
		= &data->fork[(i + 1) % data->num_of_philo];
	data->struct_philo[i].has_left = 0;
	data->struct_philo[i].has_right = 0;
	data->struct_philo[i].finished = 0;
	data->struct_philo[i].time_last = get_time_mili();
	if (pthread_mutex_init(&data->struct_philo[i].thread_mutex, NULL))
		return (err_msg("failed to init mutex"), 0);
	data->struct_philo[i].ref_data = data;
	return (1);
}

int	set_thread(t_data *data)
{
	int	i;

	if (data->num_of_philo == 1)
	{
		if (pthread_create(&data->thread_philo[0],
				NULL, philo_one, data))
			return (free_data(data, NULL), 0);
	}
	else
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (!init_struct_philo(data, i))
				return (free_data(data, NULL), 0);
			if (pthread_create(&data->thread_philo[i],
					NULL, philo, &data->struct_philo[i]))
				return (free_data(data, NULL), 0);
			i++;
		}
	}
	return (1);
}
