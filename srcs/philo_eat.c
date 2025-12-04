/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:05:48 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 20:14:35 by ahwang           ###   ########.fr       */
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

void	set_fork_flag(t_philo *philo, pthread_mutex_t *fork)
{
	if (fork == philo->left_fork)
		philo->has_left = 1;
	else
		philo->has_right = 1;
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				state;

	choose_fork_order(philo, &first_fork, &second_fork);
	while (get_state(philo) == ALIVE)
	{
		if (pthread_mutex_lock(first_fork))
			return (err_msg("failed to lock mutex"), 0);
		set_fork_flag(philo, first_fork);
		if (!philo_print(philo, "has taken a fork"))
			return (return_forks(philo), 0);
		state = get_state(philo);
		if (state == DEAD)
			return (return_forks(philo), 0);
		if (pthread_mutex_lock(second_fork))
			return (err_msg("failed to lock mutex"), return_forks(philo), 0);
		set_fork_flag(philo, second_fork);
		if (!philo_print(philo, "has taken a fork"))
			return (return_forks(philo), 0);
		return (1);
	}
	return (0);
}

int	return_forks(t_philo *philo)
{
	if (philo->has_left)
	{
		philo->has_left = 0;
		if (pthread_mutex_unlock(philo->left_fork))
			return (err_msg("failed to unlock mutex"), 0);
	}
	if (philo->has_right)
	{
		philo->has_right = 0;
		if (pthread_mutex_unlock(philo->right_fork))
			return (err_msg("failed to unlock mutex"), 0);
	}
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
		{
			pthread_mutex_unlock(&philo->thread_mutex);
			return (return_forks(philo), 0);
		}
	}
	(*eat)++;
	if (pthread_mutex_unlock(&philo->thread_mutex))
		return (err_msg("failed to unlock mutex"), 0);
	custom_usleep_philo(philo, philo->ref_data->time_to_eat);
	if (!return_forks(philo))
		return (0);
	return (1);
}
