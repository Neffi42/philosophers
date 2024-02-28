/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 22:34:32 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define USE "USE: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ARG ": ARG must be a positive int\n"
# define NBR ": there can't be more than 300 philosophers\n"
# define FCT ": FCT failed\n"

typedef struct timeval	t_timeval;
typedef struct sem_t	t_sem;
typedef t_sem			t_fork;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	HAS_FORK,
	DEAD
}	t_state;

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
	t_sem	*run;
	t_sem	*meals;
	t_sem	*write;
	time_t	s_time;
}	t_vars;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	time_t		last_meal;
	pthread_t	thread;
	t_rules		*rules;
	t_vars		*vars;
	t_fork		*fork;
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

int		error(char *message, char *el);
int		destroy(t_philo *philos, int total_nb);
int		ft_usleep(t_philo *philo, int time_to_sleep);

#endif
