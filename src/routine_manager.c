/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:44:36 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/22 17:12:57 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_finish_all_meals(t_philo *philo)
{
	printf("\nDebut de philo finish all meals\n");
	pthread_mutex_lock(philo->meal_mtx);
	if (philo->nb_eaten == philo->data->nb_times_eat)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	printf("Fin de philo finish all meals\n");
	return (FALSE);
}

int	all_ate_flag(t_philo *philo)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	printf("\nDebut de all ate flag\n");
	while (i < philo->data->nb_philo)
	{
		if (philo_finish_all_meals(&philo[i]) == TRUE)
			count++;
		i++;
	}
	if (count == philo->data->nb_philo)
	{
		pthread_mutex_lock(philo->meal_mtx);
		philo->data->all_ate = 1;
		philo->data->end = 1;
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	printf("Fin de all ate flag\n");
	return (FALSE);
}

aize_t	measure_time()

static int	philo_is_dead(t_philo *philo)
{
	struct timeval	tv;

	printf("\nDebut de philo is dead\n");
	pthread_mutex_lock(philo->meal_mtx);
	if (gettimeofday(&tv, NULL) - philo->last_meal >= philo->data->time_to_die)
	{
		printf("  %d  -  %zu  = %lu\n", gettimeofday(&tv, NULL), philo->last_meal, (gettimeofday(&tv, NULL) - philo->last_meal));
		printf("  %zu\n", philo->data->time_to_die);
		printf("  %lu >= %zu ?\n", (gettimeofday(&tv, NULL) - philo->last_meal), philo->data->time_to_die);
		pthread_mutex_unlock(philo->meal_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	printf("Fin de philo is dead\n");
	return (FALSE);
}

int	dead_flag(t_philo *philo)
{
	size_t		i;

	i = 0;
	printf("\nDebut de dead flag\n");
	while (i < philo->data->nb_philo)
	{
		if (philo_is_dead(&philo[i]) == TRUE)
		{
			print_state_message(&philo[i], "died", i);
			pthread_mutex_lock(philo->dead_mtx);
			philo->data->dead = 1;
			philo->data->end = 1;
			pthread_mutex_unlock(philo->dead_mtx);
			return (TRUE);
		}
		i++;
	}
	printf("Fin de dead flag\n");
	return (FALSE);
}
