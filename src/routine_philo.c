/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/26 12:16:21 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_mtx);
	return (FALSE);
}

static int	left_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (check_if_dead(philo))
		return (TRUE);
	print_status_message(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->rfork);
	if (check_if_dead(philo))
		return (TRUE);
	print_status_message(philo, "has taken a fork", philo->id);
	return (FALSE);
}

static int	right_handed(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	if (check_if_dead(philo))
		return (TRUE);
	print_status_message(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->lfork);
	if (check_if_dead(philo))
		return (TRUE);
	print_status_message(philo, "has taken a fork", philo->id);
	return (FALSE);
}

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
	if ((philo->id & 1) == 0 && right_handed(philo))
		return ;
	else if (left_handed(philo))
		return ;
	print_status_message(philo, "is eating", philo->id);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = ft_gettimeofday(philo->data);
	pthread_mutex_unlock(philo->meal_mtx);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->meal_mtx);
	philo->nb_eaten += 1;
	pthread_mutex_unlock(philo->meal_mtx);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
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
