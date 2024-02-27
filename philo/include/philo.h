/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 11:18:54 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

# define USAGE "Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ARGUMENT ": argument must be a positive int\n"
# define NBR_PHILO ": there can't be more than 300 philosophers\n"
# define FUNCTION ": function failed\n"

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	HAS_FORK,
	DEAD
}	t_state;

typedef struct s_var
{
	pthread_mutex_t	mutex;
	int				content;
}	t_var;

typedef struct timeval	t_timeval;
typedef t_var			t_fork;

typedef struct s_rules
{
	int	total_nb;
	int	total_eat;
	int	time_die;
	int	time_eat;
	int	time_sleep;
}	t_rules;

typedef struct s_shared
{
	t_var			finished;
	t_var			start;
	pthread_mutex_t	write;
	long long		start_time;
}	t_shared;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	long long	last_meal;
	t_state		state;
	t_rules		*rules;
	t_shared	*shared;
	t_fork		fork;
	pthread_t	thread;
	t_fork		*fork2;
}	t_philo;

size_t		ft_strlen(char *str);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);

char		*find_message(t_state state);
t_state		find_new_state(t_state state);
int			print_state(t_philo *philo);
long long	get_time(t_philo *philo, long long *time);
int			sim_error(t_philo *philo, char *message, char *el);

int			die(t_philo *philo, long long time);
int			eating(t_philo *philo, long long time);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo, long long time);

void		*routine(void *arg);

int			check_arg(int *data, const char *av);
int			check_rules(int ac, const char **av, t_rules *rules);
int			error(char *message, char *el);
int			destroy(t_philo *philos, int total_nb);

int			init_var(t_var *var, int val);
void		incr_var(t_var *var);
void		set_var(t_var *var, int val);
int			get_var(t_var *var);

#endif
