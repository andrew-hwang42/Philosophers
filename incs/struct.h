/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:36:23 by ahwang            #+#    #+#             */
/*   Updated: 2025/06/12 11:46:29 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ALIVE		1
# define DEAD		2
# define FULL		3

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	size_t			time_last;
	pthread_mutex_t	thread_mutex;
	struct s_data	*ref_data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				state;
	size_t			time_start;
	pthread_t		*thread_philo;
	pthread_mutex_t	*fork;
	t_philo			*struct_philo;
	pthread_mutex_t	global_mutex_state;
	pthread_mutex_t	global_mutex_print;
}	t_data;

#endif
