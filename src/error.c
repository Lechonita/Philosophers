/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:35:48 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 16:37:37 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

void	free_all_exit(t_data *data, char *str)
{
	size_t		i;

	i = 0;
	printf("%s\n", str);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_mtx);
	pthread_mutex_destroy(&data->all_ate_mtx);
	pthread_mutex_destroy(&(data->end_mtx));
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	exit(1);
}
