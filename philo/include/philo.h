/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 10:30:28 by abasdere         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

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
	int				finished;
	int				start;
	pthread_mutex_t	mutex_finished;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_start;
}	t_shared;

typedef struct s_philo
{
	t_rules			rules;
	t_state			state;
	pthread_t		thread;
	long long		last_meal;
	int				fork;
	int				*fork2;
	int				nb;
	int				*start;
	int				*finished;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	*mutex_fork2;
	pthread_mutex_t	*mutex_finished;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_start;
}	t_philo;

size_t			ft_strlen(char *str);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);

int				init_philos(t_philo *philos, t_shared *shared, t_rules rules);
int				init_shared(t_shared *shared);

char			*find_message(t_state state);
t_state			find_new_state(t_state state);

void			*routine(void *arg);

int				error(char *message, char *el);
int				destroy(t_philo *philos, int total_nb);

#endif
