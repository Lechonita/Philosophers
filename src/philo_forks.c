/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:53:43 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/28 16:47:01 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_release_forks_error(t_philo *philo)
{
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->data->forks[0]);
	else if (philo->id == philo->data->nb_philo)
		pthread_mutex_unlock(&philo->data->forks[0]);
	else if ((philo->id & 1) == 0)
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	else
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
}

int	uneven_philo_pick_fork(t_philo *philo)
{
	if ((philo->id & 1) != 0)
	{
		if (check_stop_status(philo) == TRUE)
			return (ERROR);
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		print_status_message(philo, "has taken a fork", philo->id);
		if (check_stop_status(philo) == TRUE)
			return (ERROR_RLS);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
		return (TRUE);
	}
	return (FALSE);
}

int	even_philo_pick_fork(t_philo *philo)
{
	if ((philo->id & 1) == 0)
	{
		if (check_stop_status(philo) == TRUE)
			return (ERROR);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print_status_message(philo, "has taken a fork", philo->id);
		if (check_stop_status(philo) == TRUE)
			return (ERROR_RLS);
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
		return (TRUE);
	}
	return (FALSE);
}

int	last_philo_pick_fork(t_philo *philo)
{
	if (philo->id == philo->data->nb_philo)
	{
		if (check_stop_status(philo) == TRUE)
			return (ERROR);
		pthread_mutex_lock(&philo->data->forks[0]);
		print_status_message(philo, "has taken a fork", philo->id);
		if (check_stop_status(philo) == TRUE)
			return (ERROR_RLS);
		pthread_mutex_lock(&philo->data->forks[philo->data->nb_philo - (philo->id - 1)]);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
		return (TRUE);
	}
	return (FALSE);
}

int	first_philo_pick_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		if (check_stop_status(philo) == TRUE)
			return (ERROR);
		pthread_mutex_lock(&philo->data->forks[0]);
		print_status_message(philo, "has taken a fork", philo->id);
		if (check_stop_status(philo) == TRUE)
			return (ERROR_RLS);
		pthread_mutex_lock(&philo->data->forks[philo->data->nb_philo - 1]);
		print_status_message(philo, "has taken a fork", philo->id);
		print_status_message(philo, "is eating", philo->id);
		return (TRUE);
	}
	return (FALSE);
}
