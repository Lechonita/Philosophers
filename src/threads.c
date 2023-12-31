/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 17:38:41 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop_status(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mtx);
	pthread_mutex_lock(philo->dead_mtx);
	if (*philo->dead == 1 || philo->data->dead == 1 || philo->data->all_ate == 1
		|| philo->data->end == 1
		|| philo->nb_eaten >= philo->data->nb_times_eat)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_mtx);
	pthread_mutex_unlock(philo->meal_mtx);
	return (FALSE);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if ((philo->id & 1) == 0)
		usleep(100);
	while (check_stop_status(philo) == FALSE)
	{
		ft_eat(philo);
		if (check_stop_status(philo) == TRUE)
			return (NULL);
		ft_sleep(philo);
		if (check_stop_status(philo) == TRUE)
			return (NULL);
		ft_think(philo);
		if (check_stop_status(philo) == TRUE)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	*manager_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (dead_flag(philo) == TRUE || all_ate_flag(philo) == TRUE)
			break ;
		usleep(100);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_t	manager;
	size_t		i;

	if (pthread_create(&manager, NULL, &manager_routine, data->philo) != 0)
		free_all_exit(data, ERR_THCR_MAN, 3);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, &philo_routine, &data->philo[i]))
			free_all_exit(data, ERR_THCR, 3);
		i++;
	}
	i = 0;
	if (pthread_join(manager, NULL) != 0)
		free_all_exit(data, ERR_THJN_MAN, 3);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			free_all_exit(data, ERR_THJN, 3);
		i++;
	}
}
