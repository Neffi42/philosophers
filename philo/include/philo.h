/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/23 13:02:53 by abasdere         ###   ########.fr       */
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
# define ARGUMENT ": argument must be an non-null unsigned int\n"
# define FUNCTION ": function failed\n"

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	HAS_FORK,
	DYING
}	t_state;

typedef struct timeval	t_timeval;

typedef struct s_args
{
	unsigned int	total_nb;
	unsigned int	total_eat;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
}	t_args;

typedef struct s_shared
{
	unsigned int	finished;
	int				start;
	pthread_mutex_t	mutex_finished;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_start;
}	t_shared;

typedef struct s_philo
{
	t_args			args;
	t_state			state;
	pthread_t		thread;
	size_t			last_meal;
	unsigned int	fork;
	unsigned int	fork2;
	unsigned int	nb;
	int				*start;
	unsigned int	*finished;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*fork2_mutex;
	pthread_mutex_t	*mutex_finished;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_start;
}	t_philo;

size_t			ft_strlen(char *str);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_atoui(const char *nptr);
char			*ft_uitoa(unsigned int n);

int				init_philos(t_philo *philos, t_shared *shared, t_args args);
int				init_shared(t_shared *shared);

char			*find_message(t_state state);
t_state 		find_new_state(t_state state);

void			*routine(void *arg);

int				error(char *message, char *el);
int				destroy(t_philo *philos, unsigned int total_nb);

#endif
