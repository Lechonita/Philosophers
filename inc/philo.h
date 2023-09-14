/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:43:57 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/14 20:00:10 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> // memset
# include <stdint.h>
# include <unistd.h> // unsleep, gettimeofday, write
# include <stdio.h> // malloc, free, printf
# include <sys/time.h> // pthread_create, pthread_detach, pthread_join,
						// pthread_mutex_init, pthread_mutex_destroy,
						// pthread_mutex_lock, pthread_mutex_unlock
# include <pthread.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FREE 4
# define USED 5

typedef struct s_philo
{
	int			id;
	int			nb_eaten;
	int			lfork;
	int			rfork;
	int			alive;
	int			starving_time;
	int			starving_time_start;
	int			starving_time_end;
	t_state		*state;
	t_philo		*next;
}	t_philo;

typedef struct s_state
{
	int			eating;
	int			sleeping;
	int			thinking;
	int			starving;
}	t_state;

typedef struct s_fork
{
	int			id;
	int			usage;
	t_fork		*next;
}	t_fork;

typedef struct s_data
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_eat;
	t_fork		*fork;
	t_philo		*philo;
}	t_data;

#endif