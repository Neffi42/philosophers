/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 10:42:08 by abasdere         ###   ########.fr       */
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
# include <limits.h>

# define USE "USE: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ARG ": ARG must be a positive int\n"
# define NBR ": there can't be more than 300 philosophers\n"
# define FCT ": FCT failed\n"

typedef struct timeval	t_timeval;

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
	int		total_nb;
	int		total_meals;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	time_t	s_time;
}	t_rules;

typedef struct s_sems
{
	sem_t	*run;
	int		bool_run;
	sem_t	*meals;
	int		nb_meals;
	sem_t	*write;
	sem_t	*forks;
}	t_sems;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	time_t		last_meal;
	pthread_t	thread;
	t_rules		*rules;
	t_sems		*sems;
}	t_philo;

size_t	ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

int		check_rules(int ac, const char **av, t_rules *rules);

int		init_philos(t_philo *philos, t_sems *sems, t_rules *rules);
int		init_sems(t_sems *sems, int total_nb);

time_t	get_time(t_philo *philo, time_t *time);
int		print_state(t_philo *philo, t_state state);
int		is_philo_dead(t_philo *philo);
int		ft_usleep(t_philo *philo, int time_to_sleep);

void	*one_philo(t_philo *philo);

void	*routine(void *arg);

int		error(char *message, char *el);
void	unlink_sem(void);
void	close_sem(t_sems *sems);
void	destroy_sem(sem_t *sem, char *name);
int		destroy(t_philo *philos, int total_nb);

#endif
