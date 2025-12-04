/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:25:49 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 20:21:05 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	philo_loop(t_philo *philo, int *eat)
{
	int	margin;

	while (*eat != philo->ref_data->num_must_eat && get_state(philo) != DEAD)
	{
		if (!philo_print(philo, "is thinking"))
			return (set_state(philo, DEAD), return_forks(philo), 0);
		if (!philo_eat(philo, eat))
			return (set_state(philo, DEAD), return_forks(philo), 0);
		if (get_state(philo) == DEAD)
			return (return_forks(philo), 0);
		if (!philo_print(philo, "is sleeping"))
			return (set_state(philo, DEAD), return_forks(philo), 0);
		custom_usleep_philo(philo, philo->ref_data->time_to_sleep);
		if (philo->ref_data->num_of_philo % 2 == 1)
		{
			margin = philo->ref_data->time_to_die
				- (philo->ref_data->time_to_sleep
					+ philo->ref_data->time_to_eat);
			if (margin > 0)
				custom_usleep_philo(philo, margin / 2);
		}
	}
	return (1);
}

int	check_full(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to lock mutex"), 0);
	philo->finished = 1;
	if (philo->ref_data->state == DEAD)
	{
		pthread_mutex_unlock(&philo->ref_data->global_mutex_state);
		return (0);
	}
	philo->ref_data->full_count++;
	if (philo->ref_data->full_count == philo->ref_data->num_of_philo)
		philo->ref_data->state = FULL;
	if (pthread_mutex_unlock(&philo->ref_data->global_mutex_state))
		return (err_msg("failed to unlock mutex"), 0);
	return (1);
}

void	*philo(void *p)
{
	t_philo	*philo;
	int		eat;

	philo = p;
	eat = 0;
	if (pthread_mutex_lock(&philo->thread_mutex))
		return (err_msg("failed to lock mutex"), NULL);
	philo->time_last = get_time_mili();
	if (pthread_mutex_unlock(&philo->thread_mutex))
		return (err_msg("failed to unlock mutex"), NULL);
	if (philo->ref_data->num_of_philo % 2 == 1)
	{
		if (philo->id % 2 == 1)
			custom_usleep(philo->ref_data->time_to_eat);
	}
	else
		custom_usleep((philo->id % 2) * 100);
	if (!philo_loop(philo, &eat))
		return (NULL);
	check_full(philo);
	return (return_forks(philo), NULL);
}
