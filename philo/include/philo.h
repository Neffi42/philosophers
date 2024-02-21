/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 14:24:20 by abasdere         ###   ########.fr       */
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
	unsigned int	nb;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	eat_times;
}	t_args;

typedef struct s_philo
{
	unsigned int	nb;
	t_state			state;
	pthread_mutex_t	fork;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	t_args	args;
}	t_data;

size_t			ft_strlen(char *str);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_atoui(const char *nptr);
char			*ft_uitoa(unsigned int n);

void			*routine(t_philo *philo, t_args args);

int				error(char *message, char *el);
int				destroy(t_data *data);

#endif
