/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 17:04:57 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_release_forks(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->data->nb_philo - 1]);
		pthread_mutex_unlock(&philo->data->forks[0]);
	}
	else if (philo->id == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->data->nb_philo - (philo->id - 1)]);
		pthread_mutex_unlock(&philo->data->forks[0]);
	}
	else if ((philo->id & 1) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
	}
}

int	ft_pick_forks(t_philo *philo)
{
	int	res;

	if (check_stop_status(philo) == TRUE)
		return (FALSE);
	res = first_philo_pick_fork(philo);
	if (res == FALSE)
	{
		res = last_philo_pick_fork(philo);
		if (res == FALSE)
		{
			res = even_philo_pick_fork(philo);
			if (res == FALSE)
				res = uneven_philo_pick_fork(philo);
		}
	}
	if (res > 1)
	{
		if (res == ERROR_RLS)
			ft_release_forks_error(philo);
		return (FALSE);
	}
	return (TRUE);
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
	if (ft_pick_forks(philo) == FALSE)
		return ;
	pthread_mutex_lock(philo->meal_mtx);
	// printf("philo %zu last meal avant = %zu\n", philo->id, philo->last_meal);
	philo->last_meal = ft_gettimeofday(philo->data);
	// printf("philo %zu last meal = %zu\n", philo->id, philo->last_meal);
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
}
