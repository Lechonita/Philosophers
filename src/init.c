/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:11:39 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 11:36:36 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_data *data, pthread_mutex_t *forks, char **args)
{
	int				i;
	t_philo			philo[MAX_PHILO];
	struct timeval	time;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].nb_eaten = 0;
		philo[i].start_time = gettimeofday(&time, NULL);
		philo[i].start_eat = 0;
		philo[i].lfork = &forks[i];
		if (i == 0)
			philo[i].rfork = &forks[data->nb_philo - 1];
		else
			philo[i].rfork = &forks[i - 1];
		i++;
	}
}

static void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i--;
	}
}

static void	init_mutex_data(t_data *data)
{
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->sleep_lock, NULL);
	pthread_mutex_init(&data->think_lock, NULL);
	pthread_mutex_init(&data->all_ate, NULL);
}

int	init_data(t_data *data, char **args)
{
	if (ft_atoi(args[1]) >= 0 && ft_atoi(args[1]) <= MAX_PHILO)
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
	init_mutex_data(data);
	return (TRUE);
}
