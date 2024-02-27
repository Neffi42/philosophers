/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 15:07:59 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoi(av);
	if (!*data)
		return (error(ARGUMENT, (char *)av));
	tmp = ft_itoa(*data);
	if (!tmp)
		return (error(FUNCTION, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARGUMENT, (char *)av));
	if (*data <= 0)
		return (free(tmp), error(ARGUMENT, (char *)av));
	return (free(tmp), 0);
}

int	check_rules(int ac, const char **av, t_rules *rules)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&rules->total_nb, av[1])
		|| check_arg(&rules->time_die, av[2])
		|| check_arg(&rules->time_eat, av[3])
		|| check_arg(&rules->time_sleep, av[4]))
		return (1);
	if (ac == 5)
		rules->total_eat = 0;
	else if (check_arg(&rules->total_eat, av[5]))
		return (1);
	if (rules->total_nb > 300)
		return (error(NBR_PHILO, (char *)av[1]));
	return (0);
}

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

int	destroy(t_philo *philos, int total_nb)
{
	int	i;

	if (!philos)
		return (1);
	i = -1;
	while (++i < total_nb)
		if (philos[i].thread)
			pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < total_nb)
	{
		if (philos[i].id == 0)
			continue ;
		pthread_mutex_destroy(&(philos[i].fork.mutex));
		pthread_mutex_destroy(&(philos[i].finished.mutex));
	}
	pthread_mutex_destroy(&(philos->shared->start.mutex));
	pthread_mutex_destroy(&(philos->shared->write));
	return (free(philos), 1);
}
