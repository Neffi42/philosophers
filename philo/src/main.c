/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/19 23:54:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(unsigned int *data, const char *av)
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

static int	check_args(int ac, const char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&args->nb, av[1]) || check_arg(&args->die, av[2]) || \
	check_arg(&args->eat, av[3]) || check_arg(&args->sleep, av[4]))
		return (EXIT_FAILURE);
	if (ac == 5)
		args->eat_times = 0;
	else if (check_arg(&args->eat_times, av[5]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_philo	*init_philos(t_args args)
{
	t_philo	*philos;
	size_t	i;

	philos = ft_calloc(args.nb, sizeof(t_philo));
	if (!philos)
		return (error(FUNCTION, "ft_calloc"), NULL);
	i = -1;
	while (++i < args.nb)
	{
		philos[i].nb = i + 1;
		philos[i].state = THINKING;
		if (pthread_mutex_init(&philos[i].fork, NULL))
			return (error(FUNCTION, "pthread_mutex_init"),
				destr(philos, args), NULL);
	}
	return (philos);
}

static int	create_threads(t_philo *philos, t_args args)
{
	size_t	i;

	i = -1;
	while (++i < args.nb)
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			return (error(FUNCTION, "pthread_create"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, const char **av)
{
	t_args		args;
	t_philo		*philos;

	if (check_args(ac, av, &args))
		return (EXIT_FAILURE);
	philos = inti_philos(args);
	if (!philos)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
