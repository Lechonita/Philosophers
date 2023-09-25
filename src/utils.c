/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:32:00 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/25 14:38:23 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status_message(t_philo *philo, char *str, int id)
{
	size_t	tv;

	// printf("Debut de print state message\n");
	pthread_mutex_lock(philo->write_mtx);
	tv = ft_gettimeofday(philo->data) - philo->data->time_start;
	printf("%zu %d %s\n", tv, id, str);
	pthread_mutex_unlock(philo->write_mtx);
	// printf("Fin de print state message\n");
}

size_t	ft_gettimeofday(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		free_all_exit(data, ERR_TIME, 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
