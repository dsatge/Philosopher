/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:35:32 by dsatge            #+#    #+#             */
/*   Updated: 2025/05/03 14:08:18 by dsatge           ###   ########.fr       */
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

// typedef struct s_data t_data;
typedef struct s_philo t_philo;
// struct s_data;		

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
	pthread_mutex_t		**mutex_fork;
	// t_data	*data;
	t_philo		*philo;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					stop;
	int					count_meal;
	long long int		lastmeal;
	pthread_t			thread;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
	t_data				*data;
	// t_data	*data;
}	t_philo;

// typedef struct s_data
// {
// 	t_data				data;
// 	t_philo				*philo;
// }		t_data;

//UTILS
void			ft_putstrfd(char *str, int fd);
long long int	get_time_ms(void);
void			ft_usleep(long long int t_ms, t_data *data);
void			printf_status(t_philo *philo, char *str);
int				wait_for_all(t_data *data);
//PARSING
int				check_parsing(t_data *data, int ac);
int				check_data(t_data *data, int argc);
int				convert_nbr(char *str);
//STRUCT
int				init(t_data *data, int argc, char **argv);
//EXIT
int				ft_exit(t_data *data, t_philo *philo,
					int dest_data, int dest_philo);
int				ft_dell_mutexdata(t_data *data, int i);
int				ft_dell_forks(t_data *data, int i);
//PHILO
int				death_check(t_data *data);
void			*stop_routine(t_philo *philo);
int				feededphilo_check(t_data *data);
int				philo_launch(t_data *data);
//ROUTINE
void			eat(t_philo *philo, t_data *data);
int				sleep_f(t_philo *philo, t_data *data);
int				think(t_philo *philo, t_data *data);
//SURVIVE
void			starvation_death(t_philo *philo, t_data *data);
void			*last_meal(void *v_data);
#endif