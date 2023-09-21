/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 14:58:29 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	(void)ptr;
	printf("Je fais ma  routine\n");
	// manger
	// penser
	// dormir
	return (NULL);
}

void	*manager_routine(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		printf("I am Philo %zu\n", philo[i].id);
		i++;
	}
	return (NULL);
	// check si il y a un mort => alors stop
	// check si tout le monde est rassasié => alors stop
}

void	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	manager;
	size_t		i;

	if (pthread_create(&manager, NULL, &manager_routine, data->philo) != 0)
		destroy_all(data, forks, ERR_THCR_MAN);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_routine, NULL))
			destroy_all(data, forks, ERR_THCR);
		i++;
	}
	i = 0;
	if (pthread_join(manager, NULL) != 0)
		destroy_all(data, forks, ERR_THJN_MAN);
	while (i)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			destroy_all(data, forks, ERR_THJN);
		i++;
	}
}
