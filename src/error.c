/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:35:48 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 11:48:05 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

void	destroy_all(t_data *data, pthread_mutex_t *forks, char *str)
{
	int		i;

	if (pthread_mutex_destroy(&data->dead) != 0
		|| pthread_mutex_destroy(&data->eat_lock) != 0
		|| pthread_mutex_destroy(&data->sleep_lock) != 0
		|| pthread_mutex_destroy(&data->think_lock) != 0
		|| pthread_mutex_destroy(&data->all_ate) != 0)
		write(2, "Error: Mutex data destroy\n", 26);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			write(2, "Error: Mutex forks destroy\n", 27);
		i++;
	}
	if (str)
	{
		write(2, str, strlen(str));
		write(2, "\n", 1);
	}
}
