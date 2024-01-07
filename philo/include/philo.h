/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/07 15:59:05 by abasdere         ###   ########.fr       */
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
# define OVERFLOW "Error: arguments must be unsigned ints\n"
# define MEMORY "Error: memory allocation failed\n"

typedef struct s_philo
{
	unsigned int	nb;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	eat_times;
}	t_philo;

int				error(char *message);
size_t			ft_strlen(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_atoui(const char *nptr);
char			*ft_uitoa(unsigned int n);

#endif
