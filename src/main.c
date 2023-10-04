/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:02:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/10/04 11:27:38 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] <= '0' && args[i][j] >= '9')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	main(int ac, char **args)
{
	t_data	data;

	if (check_args(args) == TRUE && (ac == 5 || ac == 6))
	{
		data = (t_data){0};
		if (init_data(&data, args) == TRUE)
		{
			init_mutex(&data);
			init_philo(&data);
			create_threads(&data);
			free_all_exit(&data, NULL, 4);
		}
	}
	else
		return (write(1, ERR_ARGS, 31));
	return (0);
}
