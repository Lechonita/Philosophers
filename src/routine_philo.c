/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:40:34 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/22 17:06:58 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	printf("\nDebut de ft_eat\n");
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->dead_mtx);
		philo->data->end = 1;
		pthread_mutex_unlock(philo->dead_mtx);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(philo->lfork);
	print_state_message(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->rfork);
	print_state_message(philo, "has taken a fork", philo->id);
	print_state_message(philo, "is eating", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = ft_gettimeofday(philo->data);
	philo->nb_eaten += 1;
	pthread_mutex_unlock(philo->meal_mtx);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	printf("Fin de ft_eat\n");
}

void	ft_sleep(t_philo *philo)
{
	printf("\nDebut de ft_sleep\n");
	if (philo->data->end == 1)
		return ;
	print_state_message(philo, "is sleeping", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	printf("Fin de ft_sleep\n");
}

void	ft_think(t_philo *philo)
{
	printf("\nDebut de ft_think\n");
	if (philo->data->end == 1)
		return ;
	print_state_message(philo, "is thinking", philo->id);
	printf("Fin de ft_think\n");
}
