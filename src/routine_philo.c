/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/26 15:31:34 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->dead_mtx);
		philo->data->end = 1;
		pthread_mutex_unlock(philo->dead_mtx);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	printf("Pour philo id = %zu\n", philo->id);
	if ((philo->id & 1) == 0 && ft_eat_right_handed(philo) == TRUE)
		return ;
	else if (ft_eat_left_handed(philo) == TRUE)
		return ;
	// if (lock_forks_mutex(philo) == TRUE)
	// 	return ;
	print_status_message(philo, "is eating", philo->id);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = ft_gettimeofday(philo->data);
	pthread_mutex_unlock(philo->meal_mtx);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->meal_mtx);
	philo->nb_eaten += 1;
	pthread_mutex_unlock(philo->meal_mtx);
	unlock_forks_mutex(philo);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mtx);
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		pthread_mutex_unlock(philo->meal_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	pthread_mutex_unlock(philo->meal_mtx);
	print_status_message(philo, "is sleeping", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	print_status_message(philo, "is thinking", philo->id);
	if (philo->data->time_to_eat >= philo->data->time_to_sleep)
		usleep(philo->data->time_to_eat - philo->data->time_to_sleep + 1);
}
