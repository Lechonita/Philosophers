/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:43:57 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 11:48:49 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> // timeofday
# include <pthread.h> // thread & mutex
# include <stdlib.h> // malloc
# include <string.h> // memset
# include <stdint.h>
# include <unistd.h> // unsleep, gettimeofday, write
# include <stdio.h> // malloc, free, printf
# include <sys/time.h> // pthread_create, pthread_detach, pthread_join,
						// pthread_mutex_init, pthread_mutex_destroy,
						// pthread_mutex_lock, pthread_mutex_unlock

# define MAX_PHILO 200

# define FALSE 0
# define TRUE 1

# define EAT 0
# define SLEEP 1
# define THINK 2
// # define FREE 4
// # define USED 5

# define ERR_ARGS "Error: Invalid input arguments\n"
# define ERR_NB_PHILO "Error: invalid number of philosophers\n"
# define ERR_T_DIE "Error: Invalid time to die\n"
# define ERR_T_EAT "Error: Invalid time to eat\n"
# define ERR_T_SLEEP "Error: Invalid time to sleep\n"
# define ERR_THCR_MAN "Error: Manager thread creation\n"
# define ERR_THCR "Error: Philo thread creation\n"
# define ERR_THJN "Error: Philo thread join\n"

typedef struct s_philo
{
	pthread_t			thread;
	size_t				id;
	size_t				nb_eaten;
	size_t				start_time;
	size_t				start_eat;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		sleep_lock;
	pthread_mutex_t		think_lock;
}	t_philo;

typedef struct s_data
{
	size_t				nb_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				nb_times_eat;
	size_t				dead;
	size_t				all_ate;
	pthread_mutex_t		dead;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		sleep_lock;
	pthread_mutex_t		think_lock;
	pthread_mutex_t		all_ate;
	t_philo				*philo;
}	t_data;

/* ERRO */
void	destroy_all(t_data *data, pthread_mutex_t *forks, char *str);

/* UTILS */
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif