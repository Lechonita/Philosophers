/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:35:48 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/25 15:48:16 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

void	free_all_exit(t_data *data, char *str, int error)
{
	size_t		i;

	i = 0;
	if (str)
		printf("%s\n", str);
	if (error != 0)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&data->dead_mtx);
		pthread_mutex_destroy(&data->meal_mtx);
		pthread_mutex_destroy(&(data->write_mtx));
	}
	if (data->philo)
		free(data->philo);
	data->philo = NULL;
	if (data->forks)
		free(data->forks);
	data->forks = NULL;
	exit(1);
}
