/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:20:17 by ahwang            #+#    #+#             */
/*   Updated: 2025/08/29 22:55:35 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->global_mutex_state, NULL))
		return (0);
	if (pthread_mutex_init(&data->global_mutex_print, NULL))
		return (0);
	return (1);
}

int	init_struct_data(char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->num_of_philo = ft_modified_atoi(argv[1]);
	data->time_to_die = ft_modified_atoi(argv[2]);
	data->time_to_eat = ft_modified_atoi(argv[3]);
	data->time_to_sleep = ft_modified_atoi(argv[4]);
	data->num_must_eat = -1;
	if (argv[5])
		data->num_must_eat = ft_modified_atoi(argv[5]);
	if (!data->num_of_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_eat || !data->time_to_sleep
		|| !data->num_must_eat)
		return (0);
	data->state = ALIVE;
	data->time_start = get_time_mili();
	data->thread_philo = malloc(data->num_of_philo * sizeof(pthread_t));
	data->fork = malloc(data->num_of_philo * sizeof(pthread_mutex_t));
	data->struct_philo = malloc(data->num_of_philo * sizeof(t_philo));
	if (!data->thread_philo || !data->fork || !data->struct_philo)
		return (free_data(data, "malloc failed"), 0);
	if (!init_mutex(data))
		return (free_data(data, "failed to init mutex"), 0);
	return (1);
}
