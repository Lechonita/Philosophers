/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:35:48 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 20:00:28 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

void	init_data(t_data *data, char **args)
{
	data->nb_philo = args[1];
	data->time_to_die = args[2];
	data->time_to_eat = args[3];
	data->time_to_sleep = args[4];
	if (args[5])
		data->nb_eat = args[5];
	else
		data->nb_eat = -1;
	// init_philo(data, args);
	// init_fork(data, args[1]);
}
