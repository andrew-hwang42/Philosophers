/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:06:26 by ahwang            #+#    #+#             */
/*   Updated: 2025/08/29 06:45:50 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	philo_print(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->ref_data->global_mutex_print))
		return (err_msg("failed to lock mutex"), 0);
	printf("%ld ", get_time_mili() - philo->ref_data->time_start);
	printf("%d %s\n", philo->id, str);
	if (pthread_mutex_unlock(&philo->ref_data->global_mutex_print))
		return (err_msg("failed to unlock mutex"), 0);
	return (1);
}

int	get_state(t_philo *philo)
{
	int	state;

	if (pthread_mutex_lock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to lock mutex"), 0);
	state = philo->ref_data->state;
	if (pthread_mutex_unlock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to unlock mutex"), 0);
	return (state);
}

int	set_state(t_philo *philo, int state)
{
	if (pthread_mutex_lock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to lock mutex"), 0);
	philo->ref_data->state = state;
	if (pthread_mutex_unlock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to unlock mutex"), 0);
	return (1);
}

void	*philo_one(void *p)
{
	t_data	*data;

	data = p;
	if (!init_struct_philo(data, 0))
		return (free_data(data, NULL), NULL);
	if (!philo_print(&data->struct_philo[0], "is thinking"))
		return (NULL);
	if (pthread_mutex_lock(data->struct_philo[0].left_fork))
		return (err_msg("failed to lock mutex"), NULL);
	if (!philo_print(&data->struct_philo[0], "has taken a fork"))
		return (NULL);
	if (pthread_mutex_unlock(data->struct_philo[0].left_fork))
		return (err_msg("failed to unlock mutex"), NULL);
	custom_usleep(data->time_to_die);
	if (!philo_print(&data->struct_philo[0], "died"))
		return (NULL);
	return (NULL);
}
