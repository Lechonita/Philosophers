/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:45:26 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 19:51:12 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			return (0);
		i++;
	}
}
