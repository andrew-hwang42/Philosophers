/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:20:52 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 20:21:37 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	err_msg(char *msg)
{
	printf("Error: %s\n", msg);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_modified_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (err_msg("invalid character exists"), 0);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (ft_strlen(str) > ft_strlen("2147483647")
		|| nbr > 2147483647)
		return (err_msg("out of int range"), 0);
	return (nbr);
}

void	free_data(t_data *data, char *msg)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->thread_philo[i], NULL);
	pthread_mutex_destroy(&data->global_mutex_print);
	pthread_mutex_destroy(&data->global_mutex_state);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->struct_philo[i].thread_mutex);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	if (data->thread_philo)
		free(data->thread_philo);
	if (data->fork)
		free(data->fork);
	if (data->struct_philo)
		free(data->struct_philo);
	if (msg)
		err_msg(msg);
}
