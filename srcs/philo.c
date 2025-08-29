/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:25:49 by ahwang            #+#    #+#             */
/*   Updated: 2025/08/29 06:52:00 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	choose_fork_order(t_philo *philo,
			pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	choose_fork_order(philo, &first_fork, &second_fork);
	if (pthread_mutex_lock(first_fork))
		return (err_msg("failed to lock mutex"), 0);
	if (get_state(philo) == DEAD)
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	if (!philo_print(philo, "has taken a fork"))
		return (0);
	if (pthread_mutex_lock(second_fork))
		return (err_msg("failed to lock mutex"), 0);
	if (get_state(philo) == DEAD)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (0);
	}
	if (!philo_print(philo, "has taken a fork"))
		return (0);
	return (1);
}

int	return_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork))
		return (err_msg("failed to unlock mutex"), 0);
	if (pthread_mutex_unlock(philo->right_fork))
		return (err_msg("failed to unlock mutex"), 0);
	return (1);
}

int	philo_eat(t_philo *philo, int *eat)
{
	if (!take_forks(philo))
		return (0);
	if (pthread_mutex_lock(&philo->thread_mutex))
		return (err_msg("failed to lock mutex"), 0);
	philo->time_last = get_time_mili();
	if (*eat != -1)
	{
		if (!philo_print(philo, "is eating"))
			return (return_forks(philo), 0);
	}
	(*eat)++;
	if (pthread_mutex_unlock(&philo->thread_mutex))
		return (err_msg("failed to unlock mutex"), 0);
	custom_usleep(philo->ref_data->time_to_eat);
	if (!return_forks(philo))
		return (0);
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
	custom_usleep((philo->id % 2) * 30);
	while (eat != philo->ref_data->num_must_eat && get_state(philo) == ALIVE)
	{
		if (!philo_print(philo, "is thinking"))
			return (set_state(philo, DEAD), NULL);
		if (!philo_eat(philo, &eat))
			return (set_state(philo, DEAD), NULL);
		if (get_state(philo) == DEAD)
			return (NULL);
		if (!philo_print(philo, "is sleeping"))
			return (set_state(philo, DEAD), NULL);
		custom_usleep(philo->ref_data->time_to_sleep);
	}
	set_state(philo, FULL);
	return (NULL);
}
