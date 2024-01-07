/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/07 17:12:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(unsigned int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoui(av);
	if (!*data)
		return (error(ARGUMENT, (char *)av));
	tmp = ft_uitoa(*data);
	if (!tmp)
		return (error(FUNCTION, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARGUMENT, (char *)av));
	return (free(tmp), EXIT_SUCCESS);
}

int	main(int ac, const char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_args(&philo.nb, av[1]) || check_args(&philo.die, av[2]) || \
	check_args(&philo.eat, av[3]) || check_args(&philo.sleep, av[4]))
		return (EXIT_FAILURE);
	if (ac == 5)
		philo.eat_times = 0;
	else if (check_args(&philo.eat_times, av[5]))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&philo.mutex, NULL))
		return (error(FUNCTION, "pthread_mutex_init"));
	if (pthread_mutex_destroy(&philo.mutex))
		return (error(FUNCTION, "pthread_mutex_destroy"));
	return (EXIT_SUCCESS);
}
