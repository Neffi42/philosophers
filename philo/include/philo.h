/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 09:43:17 by abasdere         ###   ########.fr       */
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
# include <limits.h>

# define USE "USE: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ARG ": ARG must be a positive int\n"
# define NBR ": there can't be more than 300 philosophers\n"
# define FCT ": FCT failed\n"

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
	int	total_meals;
	int	time_die;
	int	time_eat;
	int	time_sleep;
}	t_rules;

typedef struct s_vars
{
	t_var			run;
	t_var			meals;
	pthread_mutex_t	write;
	time_t			s_time;
}	t_vars;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	time_t		last_meal;
	t_rules		*rules;
	t_vars		*vars;
	t_fork		fork;
	pthread_t	thread;
	t_fork		*fork2;
}	t_philo;

size_t	ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

int		check_rules(int ac, const char **av, t_rules *rules);

int		init_philos(t_philo *philos, t_vars *vars, t_rules *rules);
int		init_vars(t_vars *vars);

int		print_state(t_philo *philo, t_state state);
time_t	get_time(t_philo *philo, time_t *time);
int		is_philo_dead(t_philo *philo);
int		ft_usleep(t_philo *philo, int time_to_sleep);

void	*routine(void *arg);

int		error(char *message, char *el);
int		destroy(t_philo *philos, int total_nb);

int		init_var(t_var *var, int val);
void	incr_var(t_var *var);
void	set_var(t_var *var, int val);
int		get_var(t_var *var);

#endif
