/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 18:13:43 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1/number_of_philosophers    2/time_to_die    3/time_to_eat    4/time_to_sleep
// 5/number_of_times_each_philosopher_must_eat

/* Chaque philo prend la fourchette avec le plus petit chiffre.
	Celui qui aura la plus petite et plus grande fourchette n'en prendra
	donc aucune. */

/* Créer un thread manager / serveur qui donne la permission aux philos
	de manger. Mais aussi check s'il y a un mort.
	Si oui, on arrête le programme. */

/* Rajouter une fonction qui fait attendre que tous les threads soient
	créés avant qu'ils ne s'activent. Comme ca tout le monde commence en même
	temps, personne ne prend de l'avance. 
	Est-ce que ca peut être contré direct avec un timeofday chacun ? */

static int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] >= '0' && args[i][j] <= '9')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	main(int ac, char **args)
{
	t_data			*data;

	if (check_args(args) == TRUE && (ac == 5 || ac == 6))
	{
		data = ft_calloc(1, sizeof(t_data));
		if (init_data(data, args) == TRUE)
		{
			init_mutex(data);
			init_philo(data);
			create_threads(data);
			free_struct(data, NULL, 4);
		}
	}
	else
		return (write(1, ERR_ARGS, 31));
	return (0);
}
