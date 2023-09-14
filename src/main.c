/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 19:44:53 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

int	main(int ac, char **args)
{
	t_data	*data;

	if (ac < 6 || ac > 7)
		return (0);
	if (check_args(args))
	{
		data = ft_calloc(1, sizeof(t_data));
		init_data(data, args);
	}
}
