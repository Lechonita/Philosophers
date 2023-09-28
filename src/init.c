/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:11:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 16:29:51 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_eaten = 0;
		data->philo[i].last_meal = data->time_start;
		data->philo[i].dead = &data->dead;
		data->philo[i].dead_mtx = &data->dead_mtx;
		data->philo[i].meal_mtx = &data->meal_mtx;
		data->philo[i].write_mtx = &data->write_mtx;
		data->philo[i].data = data;
		i++;
	}
}

void	init_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			free_all_exit(data, ERR_MTX_INIT, 1);
		i++;
	}
	if (pthread_mutex_init(&data->dead_mtx, NULL) != 0
		|| pthread_mutex_init(&data->meal_mtx, NULL) != 0
		|| pthread_mutex_init(&data->write_mtx, NULL) != 0)
		free_all_exit(data, ERR_MTX_DATA, 1);
}

static void	init_alloc(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		free_all_exit(data, ERR_ALLOC, 0);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		free_all_exit(data, ERR_ALLOC, 0);
}

int	init_data(t_data *data, char **args)
{
	if (ft_atoi(args[1]) > 0)
		data->nb_philo = (size_t)ft_atoi(args[1]);
	else
		return (write(1, ERR_NB_PHILO, 38), FALSE);
	if (args[5] && ft_atoi(args[5]) > 0)
		data->nb_times_eat = (size_t)ft_atoi(args[5]);
	else if (args[5] && ft_atoi(args[5]) <= 0)
		return (write(1, ERR_NB_EAT, 31), FALSE);
	else
		data->nb_times_eat = -1;
	if (ft_atoi(args[2]) > 0)
		data->time_to_die = ft_atoi(args[2]);
	else
		return (write(1, ERR_T_DIE, 27), FALSE);
	if (ft_atoi(args[3]) > 0)
		data->time_to_eat = ft_atoi(args[3]);
	else
		return (write(1, ERR_T_EAT, 27), FALSE);
	if (ft_atoi(args[4]) > 0)
		data->time_to_sleep = ft_atoi(args[4]);
	else
		return (write(1, ERR_T_SLEEP, 29), FALSE);
	data->time_start = ft_gettimeofday(data);
	init_alloc(data);
	return (TRUE);
}
