/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:11:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 16:37:56 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data, pthread_mutex_t *forks)
{
	size_t			i;
	struct timeval	time;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].nb_eaten = 0;
		data->philo[i].start_time = gettimeofday(&time, NULL);
		data->philo[i].start_eat = 0;
		data->philo[i].lfork = &forks[i];
		if (i == 0)
			data->philo[i].rfork = &forks[data->nb_philo - 1];
		else
			data->philo[i].rfork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, size_t nb_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			write(2, "Error: Mutex forks init\n", 24);
		i--;
	}
}

static void	init_alloc(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo)
	if (!data->forks)
		destroy_all
}

int	init_data(t_data *data, char **args)
{
	if (ft_atoi(args[1]) > 0)
		data->nb_philo = ft_atoi(args[1]);
	else
		return (write(1, ERR_NB_PHILO, 38), FALSE);
	if (ft_atoi(args[2]) >= 0)
		data->time_to_die = ft_atoi(args[2]);
	else
		return (write(1, ERR_T_DIE, 27), FALSE);
	if (ft_atoi(args[3]) >= 0)
		data->time_to_eat = ft_atoi(args[3]);
	else
		return (write(1, ERR_T_EAT, 27), FALSE);
	if (ft_atoi(args[4]) >= 0)
		data->time_to_sleep = ft_atoi(args[4]);
	else
		return (write(1, ERR_T_SLEEP, 29), FALSE);
	if (args[5] && ft_atoi(args[5]) >= 0)
		data->nb_times_eat = ft_atoi(args[5]);
	else
		data->nb_times_eat = -1;
	init_alloc(data);
	return (TRUE);
}
