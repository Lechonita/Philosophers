/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 19:02:48 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_release_forks(t_philo *philo)
{
	if ((philo->id & 1) == 0)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
}

void	ft_pick_forks(t_philo *philo)
{
	if ((philo->id & 1) == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_status_message(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->rfork);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_status_message(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->lfork);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1 || *philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->dead_mtx);
		philo->data->end = 1;
		pthread_mutex_unlock(philo->dead_mtx);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	ft_pick_forks(philo);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = ft_gettimeofday(philo->data);
	philo->nb_eaten += 1;
	pthread_mutex_unlock(philo->meal_mtx);
	usleep(philo->data->time_to_eat * 1000);
	ft_release_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1 || *philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	print_status_message(philo, "is sleeping", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->end == 1 || *philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->dead_mtx);
	print_status_message(philo, "is thinking", philo->id);
	if (philo->data->time_to_eat >= philo->data->time_to_sleep)
		usleep(philo->data->time_to_eat - philo->data->time_to_sleep + 1);
	else
		usleep(50);
}
