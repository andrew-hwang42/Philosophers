/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 04:20:26 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/04 20:28:28 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include "./struct.h"

/* main.c */
int		main(int argc, char **argv);

/* init_struct_data.c */
int		init_mutex(t_data *data);
int		init_struct_data(char **argv, t_data *data);

/* set_thread.c */
int		init_struct_philo(t_data *data, int i);
int		set_thread(t_data *data);

/* philo.c */
int		philo_loop(t_philo *philo, int *eat);
int		check_full(t_philo *philo);
void	*philo(void *data);

/* philo_eat.c */
void	choose_fork_order(t_philo *philo,
			pthread_mutex_t **first_fork, pthread_mutex_t **second_fork);
void	set_fork_flag(t_philo *philo, pthread_mutex_t *fork);
int		take_forks(t_philo *philo);
int		return_forks(t_philo *philo);
int		philo_eat(t_philo *philo, int *eat);

/* monitoring.c */
int		death_checker(t_data *data, int i, size_t now);
int		check_each_philo(t_data *data, int i);
int		monitoring(t_data *data);

/* philo_utils.c */
int		philo_print(t_philo *philo, char *str);
int		philo_print_die(t_philo *philo);
int		get_state(t_philo *philo);
int		set_state(t_philo *philo, int state);
void	*philo_one(void *p);

/* utils_time.c */
size_t	get_time_mili(void);
size_t	get_time_micro(void);
void	custom_usleep(size_t timecheck);
void	custom_usleep_philo(t_philo *philo, size_t timecheck);

/* utils.c */
void	err_msg(char *msg);
int		ft_strlen(char *str);
int		ft_modified_atoi(char *str);
void	free_data(t_data *data, char *msg);

#endif
