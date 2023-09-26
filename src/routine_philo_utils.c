/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:48:23 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/26 17:23:56 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	unlock_forks_mutex(t_philo *philo)
// {
// 	if ((philo->id & 1) == 0)
// 	{
// 		pthread_mutex_unlock(philo->rfork);
// 		pthread_mutex_unlock(philo->lfork);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(philo->lfork);
// 		pthread_mutex_unlock(philo->rfork);
// 	}
// }

// int	ft_eat_left_handed(t_philo *philo)
// {
// 	// printf("Je rentre dans eat_left_handed %zu\n", philo->id);
// 	pthread_mutex_lock(philo->lfork);
// 	if (check_if_dead_or_ate(philo))
// 	{
// 		pthread_mutex_unlock(philo->lfork);
// 		return (TRUE);
// 	}
// 	print_status_message(philo, "has taken a fork", philo->id);
// 	pthread_mutex_lock(philo->rfork);
// 	if (check_if_dead_or_ate(philo))
// 	{
// 		pthread_mutex_unlock(philo->rfork);
// 		pthread_mutex_unlock(philo->lfork);
// 		return (TRUE);
// 	}
// 	print_status_message(philo, "has taken a fork", philo->id);
// 	return (FALSE);
// }

// int	ft_eat_right_handed(t_philo *philo)
// {
// 	// printf("Je rentre dans eat_right_handed %zu\n", philo->id);
// 	pthread_mutex_lock(philo->rfork);
// 	if (check_if_dead_or_ate(philo))
// 	{
// 		pthread_mutex_unlock(philo->rfork);
// 		return (TRUE);
// 	}
// 	print_status_message(philo, "has taken a fork", philo->id);
// 	pthread_mutex_lock(philo->lfork);
// 	if (check_if_dead_or_ate(philo))
// 	{
// 		pthread_mutex_unlock(philo->lfork);
// 		pthread_mutex_unlock(philo->rfork);
// 		return (TRUE);
// 	}
// 	print_status_message(philo, "has taken a fork", philo->id);
// 	return (FALSE);
// }

// int	lock_forks_mutex(t_philo *philo)
// {
// 	if ((philo->id & 1) == 0 && ft_eat_right_handed(philo) == TRUE)
// 		return (TRUE);
// 	else if (ft_eat_left_handed(philo) == TRUE)
// 		return (TRUE);
// 	return (FALSE);
// }

int	check_if_dead_or_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	pthread_mutex_lock(philo->meal_mtx);
	if (philo->data->dead || philo->nb_eaten >= philo->data->nb_times_eat)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		pthread_mutex_unlock(philo->dead_mtx);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	pthread_mutex_unlock(philo->dead_mtx);
	return (FALSE);
}
