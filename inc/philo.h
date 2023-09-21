/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:43:57 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/21 18:13:28 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> // timeofday
# include <pthread.h> // thread & mutex
# include <stdlib.h> // malloc
# include <string.h> // memset
# include <stdint.h>
# include <unistd.h> // usleep, gettimeofday, write // 1M microsec = 1 sec
# include <stdio.h> // malloc, free, printf
# include <sys/time.h> // pthread_create, pthread_detach, pthread_join,
						// pthread_mutex_init, pthread_mutex_destroy,
						// pthread_mutex_lock, pthread_mutex_unlock

# define FALSE 0
# define TRUE 1

// # define EAT 0
// # define SLEEP 1
// # define THINK 2
// # define FREE 4
// # define USED 5

# define ERR_ARGS "Error: Invalid input arguments\n"
# define ERR_NB_PHILO "Error: invalid number of philosophers\n"
# define ERR_T_DIE "Error: Invalid time to die\n"
# define ERR_T_EAT "Error: Invalid time to eat\n"
# define ERR_T_SLEEP "Error: Invalid time to sleep\n"
# define ERR_THCR_MAN "Error: Manager thread creation\n"
# define ERR_THCR "Error: Philo thread creation\n"
# define ERR_THJN_MAN "Error: Manager thread join\n"
# define ERR_THJN "Error: Philo thread join\n"
# define ERR_ALLOC "Error: Memory allocation\n"
# define ERR_MT_INIT "Error: Mutex forks init\n"
# define ERR_MTX_DATA "Error: Mutex data init\n"
# define ERR_TIME "Error: Time could not be set\n"

typedef struct s_philo
{
	pthread_t			thread;
	size_t				id;
	size_t				nb_eaten;
	struct timeval		start_time;
	struct timeval		last_meal;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	struct s_data		*data;
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
	size_t				end;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		all_ate_mtx;
	pthread_mutex_t		end_mtx;
	t_philo				*philo;
}	t_data;

/* THREADS */
void	*philo_routine(void *ptr);
void	*manager_routine(void *ptr);
void	create_threads(t_data *data);

/* ERROR */
void	destroy_all(t_data *data, pthread_mutex_t *forks, char *str);

/* UTILS */
int		ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* INIT */
void	init_philo(t_data *data);
void	init_mutex(t_data *data);
int		init_data(t_data *data, char **args);

#endif