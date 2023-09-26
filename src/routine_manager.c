/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:44:36 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/26 17:09:52 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_finish_all_meals(t_philo *philo)
{
	// printf("\nDebut de philo finish all meals %zu\n", philo->nb_eaten);
	pthread_mutex_lock(philo->meal_mtx);
	if (philo->nb_eaten > 0
		&& philo->nb_eaten >= philo->data->nb_times_eat)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	// printf("Fin de philo finish all meals\n");
	return (FALSE);
}

int	all_ate_flag(t_philo *philo)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	// printf("\nDebut de all ate flag\n");
	while (i < philo->data->nb_philo)
	{
		if (philo_finish_all_meals(&philo[i]) == TRUE)
			count++;
		i++;
	}
	if (count == philo->data->nb_philo)
	{
		pthread_mutex_lock(philo->meal_mtx);
		pthread_mutex_lock(philo->dead_mtx);
		philo->data->all_ate = 1;
		philo->data->end = 1;
		pthread_mutex_unlock(philo->dead_mtx);
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	// printf("Fin de all ate flag\n");
	return (FALSE);
}

size_t	measure_last_meal(t_philo *philo, size_t last_meal)
{
	struct timeval	tv;

	// printf("\nDebut de measure last meal %zu\n", philo->id);
	if (gettimeofday(&tv, NULL) != 0)
		free_all_exit(philo->data, ERR_TIME, 2);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - last_meal);
	// printf("Fin de measure last meal %zu\n", philo->id);
}

static int	philo_is_dead(t_philo *philo)
{
	// printf("\nDebut de philo is dead %zu\n", philo->id);
	pthread_mutex_lock(philo->meal_mtx);
	if (measure_last_meal(philo, philo->last_meal) >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	// printf("Fin de philo is dead %zu\n", philo->id);
	return (FALSE);
}

int	dead_flag(t_philo *philo)
{
	size_t		i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo_is_dead(&philo[i]) == TRUE)
		{
			print_status_message(&philo[i], "died", i + 1);
			pthread_mutex_lock(philo->dead_mtx);
			philo->data->dead = 1;
			pthread_mutex_unlock(philo->dead_mtx);
			usleep(100);
			pthread_mutex_lock(philo->dead_mtx);
			philo->data->end = 1;
			pthread_mutex_unlock(philo->dead_mtx);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
