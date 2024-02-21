/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 15:10:08 by abasdere         ###   ########.fr       */
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
	return (free(tmp), 0);
}

static int	check_args(int ac, const char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&args->nb, av[1]) || check_arg(&args->die, av[2]) || \
	check_arg(&args->eat, av[3]) || check_arg(&args->sleep, av[4]))
		return (1);
	if (ac == 5)
		args->eat_times = 0;
	else if (check_arg(&args->eat_times, av[5]))
		return (1);
	return (args->start = 0, 0);
}

static int	init_philos(t_philo **philos, t_args *args)
{
	size_t	i;

	*philos = ft_calloc(args->nb, sizeof(t_philo));
	if (!(*philos))
		return (error(FUNCTION, "malloc"), 1);
	i = -1;
	while (++i < args->nb)
		(*philos)[i].nb = 0;
	i = -1;
	while (++i < args->nb)
	{
		(*philos)[i].nb = i + 1;
		(*philos)[i].state = THINKING;
		(*philos)[i].args = args;
		(*philos)[i].thread = NULL;
		if (pthread_mutex_init(&((*philos)[i].fork), NULL))
			return (error(FUNCTION, "pthread_mutex_init"), destroy(*philos));
		if (pthread_create(&((*philos)[i].thread),
			NULL, routine, &(*philos)[i]))
			return (error(FUNCTION, "pthread_create"), destroy(*philos));
	}
	return (0);
}

int	main(int ac, const char **av)
{
	t_philo	*philos;
	t_args	args;

	if (check_args(ac, av, &args))
		return (1);
	if (init_philos(&philos, &args))
		return (1);
	sleep(5);
	args.start = 1;
	return (destroy(philos), 0);
}
