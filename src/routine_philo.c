/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/25 15:56:46 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	left_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_status_message(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->rfork);
	print_status_message(philo, "has taken a fork", philo->id);
}

static void	right_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_status_message(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->lfork);
	print_status_message(philo, "has taken a fork", philo->id);
}

void	ft_eat(t_philo *philo)
{
	// printf("\nDebut de ft_eat %zu\n", philo->id);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->dead_mtx);
		philo->data->end = 1;
		pthread_mutex_unlock(philo->dead_mtx);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	if (philo->id % 2 == 0)
		right_handed(philo);
	else
		left_handed(philo);
	print_status_message(philo, "is eating", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = ft_gettimeofday(philo->data);
	philo->nb_eaten += 1;
	pthread_mutex_unlock(philo->meal_mtx);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	// printf("Fin de ft_eat %zu\n", philo->id);
}

void	ft_sleep(t_philo *philo)
{
	// printf("\nDebut de ft_sleep %zu\n", philo->id);
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	print_status_message(philo, "is sleeping", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	// printf("Fin de ft_sleep %zu\n", philo->id);
}

void	ft_think(t_philo *philo)
{
	// printf("\nDebut de ft_think %zu\n", philo->id);
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	print_status_message(philo, "is thinking", philo->id);
	// printf("Fin de ft_think %zu\n", philo->id);
}
