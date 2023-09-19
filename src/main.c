/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/19 17:07:08 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

/* Chaque philo prend la fourchette avec le plus petit chiffre.
	Celui qui aura la plus petite et plus grande fourchette n'en prendra
	donc aucune. */

/* Créer un thread manager / serveur pour qui donne la permission aux philos
	de manger ? */

static void	init_data(t_data *data, char **args)
{
	data->nb_philo = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		data->nb_times_eat = ft_atoi(args[5]);
	else
		data->nb_times_eat = -1;
}

int	main(int ac, char **args)
{
	t_data	*data;

	if (check_args(args) && (ac == 6 || ac == 7))
	{
		data = ft_calloc(1, sizeof(t_data));
		init_data(data, args);
	}
	else
		printf("Error: bad input arguments\n");
	return (0);
}
