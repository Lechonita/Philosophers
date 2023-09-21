/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 18:12:20 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop_status(t_philo *philo)
{
	int		status;

	status = FALSE;
	pthread_mutex_lock(&philo->data->dead_mtx);
	pthread_mutex_lock(&philo->data->all_ate_mtx);
	pthread_mutex_lock(&philo->data->end_mtx);
	if (philo->data->dead || philo->data->all_ate || philo->data->end)
		status = TRUE;
	pthread_mutex_unlock(&philo->data->dead_mtx);
	pthread_mutex_unlock(&philo->data->all_ate_mtx);
	pthread_mutex_unlock(&philo->data->end_mtx);
	return (status);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep (1); // ft_think
	while (check_stop_status(philo) == FALSE)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	*manager_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
		if (check_if_dead(philo) == 1 || check_if_all_ate(philo) == 1)
			break ;
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
		if (pthread_create(&data->philo[i].thread, NULL, &philo_routine, NULL))
			free_all_exit(data, ERR_THCR, 3);
		i++;
	}
	i = 0;
	if (pthread_join(manager, NULL) != 0)
		free_all_exit(data, ERR_THJN_MAN, 3);
	while (i)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			free_all_exit(data, ERR_THJN, 3);
		i++;
	}
}
