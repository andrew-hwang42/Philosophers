/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 04:20:21 by ahwang            #+#    #+#             */
/*   Updated: 2025/11/30 19:18:34 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6))
	{
		err_msg("invalid argument");
		return (1);
	}
	if (!init_struct_data(argv, &data))
		return (1);
	if (!set_thread(&data))
		return (1);
	if (!monitoring(&data))
		return (free_data(&data, NULL), 1);
	free_data(&data, NULL);
	return (0);
}
