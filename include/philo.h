/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:35:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/01 19:43:48 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

# define ERR_PARS_NODIGIT "Error: only number accepted in parameters\n"
# define ERR_PARS_OUTRANGE "Error: number out of range\n"
# define ERR_NEG_DIGIT "Error: only positiv number accepted in parameters\n"
# define ERR_MALLOC_F "Error: allocation memory failed\n"
# define ERR_PARS_ZERO "Error: parameter should be more than zero\n"
# define ERR_PARS_UP200 "Error: number of philosopher mustbe \
	below or equal to 200\n"
# define ERR_INIT_MUTEX "Error: pthread mutex init failed\n"

struct	s_general t_general;

typedef struct s_data
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_count;
	int					stop;
	long long int		start_time;
	pthread_t			thread_death;
	pthread_mutex_t		mutex_msg;
	pthread_mutex_t		mutex_eat;
	pthread_mutex_t		mutex_lastmeal;
	pthread_mutex_t		mutex_stop;
	pthread_mutex_t		mutex_countmeal;
	pthread_mutex_t		*mutex_fork;
	struct t_general	*general;
	struct t_philp		*philo;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					stop;
	long long int		lastmeal;
	pthread_t			thread;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
	t_data				*data;
	struct t_general	*general;
}	t_philo;

typedef struct s_general
{
	t_data				data;
	t_philo				*philo;
}		t_general;

//UTILS
void			ft_putstrfd(char *str, int fd);
long long int	get_time_ms(void);
void			ft_usleep(long long int t_ms, t_general *general);
void			printf_status(t_philo *philo, char *str);
int				wait_for_all(t_general *general);
//PARSING
int				check_parsing(t_general *general, int ac);
int				check_data(t_general *general, int argc);
int				convert_nbr(char *str);
//STRUCT
int				init(t_general *general, int argc, char **argv);
//EXIT
int				ft_exit(t_general *general, t_philo *philo,
					int dest_data, int dest_philo);
int				ft_dell_mutexdata(t_general *general, int i);
int				ft_dell_forks(t_data *data, int i);
//PHILO
int				death_check(t_data *data);
void			*stop_routine(t_philo *philo);
int				feededphilo_check(t_general *general);
int				philo_launch(t_general *general);
//ROUTINE
int				eat(t_philo *philo);
int				sleep_f(t_philo *philo);
int				think(t_philo *philo);
//SURVIVE
void			starvation_death(t_philo *philo);
void			*last_meal(void *v_general);
#endif