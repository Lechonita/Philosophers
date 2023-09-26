/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:43:57 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/26 17:23:49 by jrouillo         ###   ########.fr       */
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
// # define DEAD 4
// # define FORK 5

# define ERR_ARGS "Error: Invalid input arguments\n"
# define ERR_NB_PHILO "Error: invalid number of philosophers\n"
# define ERR_T_DIE "Error: Invalid time to die\n"
# define ERR_T_EAT "Error: Invalid time to eat\n"
# define ERR_T_SLEEP "Error: Invalid time to sleep\n"
# define ERR_T_INPUT "Error: Invalid time input\n"
# define ERR_NB_EAT "Error: Invalid number of meals\n"
# define ERR_THCR_MAN "Error: Manager thread creation\n"
# define ERR_THCR "Error: Philo thread creation\n"
# define ERR_THJN_MAN "Error: Manager thread join\n"
# define ERR_THJN "Error: Philo thread join\n"
# define ERR_ALLOC "Error: Memory allocation\n"
# define ERR_MTX_INIT "Error: Mutex forks init\n"
# define ERR_MTX_DATA "Error: Mutex data init\n"
# define ERR_TIME "Error: Time could not be set\n"

typedef struct s_philo
{
	pthread_t			thread;
	size_t				id;
	size_t				nb_eaten;
	size_t				last_meal;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*dead_mtx;
	pthread_mutex_t		*meal_mtx;
	pthread_mutex_t		*write_mtx;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	size_t				nb_philo;
	size_t				nb_times_eat;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				dead;
	size_t				all_ate;
	size_t				end;
	size_t				time_start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		meal_mtx;
	pthread_mutex_t		write_mtx;
	t_philo				*philo;
}	t_data;

/* INIT */
void	init_philo(t_data *data);
void	init_mutex(t_data *data);
int		init_data(t_data *data, char **args);

/* THREADS */
void	*philo_routine(void *ptr);
void	*manager_routine(void *ptr);
void	create_threads(t_data *data);

/* ROUTINE */
size_t	measure_last_meal(t_philo *philo, size_t last_meal);
int		all_ate_flag(t_philo *philo);
int		dead_flag(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);

/* ROUTINE UTILS */
// void	unlock_forks_mutex(t_philo *philo);
// int		ft_eat_left_handed(t_philo *philo);
// int		ft_eat_right_handed(t_philo *philo);
// int		lock_forks_mutex(t_philo *philo);
int		check_if_dead_or_ate(t_philo *philo);

/* UTILS */
void	print_status_message(t_philo *philo, char *str, int id);
size_t	ft_gettimeofday(t_data *data);

/* LIBFT */
int		ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* ERROR */
void	free_all_exit(t_data *data, char *str, int error);

#endif