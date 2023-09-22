/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/22 18:10:28 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop_status(t_philo *philo)
{
	printf("\nDebut de check stop status %zu\n", philo->id);
	pthread_mutex_lock(philo->meal_mtx);
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->dead || philo->data->all_ate || philo->data->end)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		pthread_mutex_unlock(philo->dead_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	pthread_mutex_unlock(philo->dead_mtx);
	printf("fin de check stop status %zu\n", philo->id);
	return (FALSE);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	// printf("\nDebut de philo routine\n");
	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep (1);
	while (check_stop_status(philo) == FALSE)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	// printf("Fin de philo routine\n");
	return (NULL);
}

void	*manager_routine(void *ptr)
{
	t_philo	*philo;

	// printf("\nDebut de manager routine\n");
	philo = (t_philo *)ptr;
	while (1)
		if (dead_flag(philo) == TRUE
			|| all_ate_flag(philo) == TRUE)
			break ;
	// printf("Fin de manager routine\n");
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_t	manager;
	size_t		i;

	// printf("\nDebut de create threads\n");
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
	// printf("Fin de create threads\n");
}
