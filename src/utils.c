/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:32:00 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 18:32:40 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_destroy(&data->write_mtx);
	}
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	exit(1);
}

void	print_status_message(t_philo *philo, char *str, int id)
{
	size_t	tv;

	pthread_mutex_lock(philo->dead_mtx);
	if (*philo->dead == 0 || philo->data->dead == 0)
	{
		pthread_mutex_lock(philo->write_mtx);
		tv = ft_gettimeofday(philo->data) - philo->data->time_start;
		printf("%zu %d %s\n", tv, id, str);
		pthread_mutex_unlock(philo->write_mtx);
	}
	pthread_mutex_unlock(philo->dead_mtx);
}

size_t	ft_gettimeofday(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		free_all_exit(data, ERR_TIME, 0);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}
