/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:52 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 11:38:42 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(char **args)
{
	
}

void	*manager_routine(char **args)
{
	
}

void	create_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	manager;
	int			i;

	if (pthread_create(&manager, NULL, &manager_routine, NULL))
		destroy_all(data, forks, ERR_THCR_MAN);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_routine, NULL))
			destroy_all(data, forks, ERR_THCR);
		i++;
	}
	i = 0;
	while (i)
	{
		if (pthread_join(&data->philo[i].thread, NULL))
			destroy_all(data, forks, ERR_THJN);
		i++;
	}
}
