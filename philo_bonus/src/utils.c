/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 10:41:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

void	unlink_sem(void)
{
	sem_unlink("run");
	sem_unlink("meals");
	sem_unlink("write");
	sem_unlink("forks");
}

void	close_sem(t_sems *sems)
{
	sem_close(sems->run);
	sem_close(sems->meals);
	sem_close(sems->write);
	sem_close(sems->forks);
}

void	destroy_sem(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

int	destroy(t_philo *philos, int total_nb)
{
	int	i;

	i = -1;
	while (++i < total_nb)
		if (philos[i].thread)
			pthread_join(philos[i].thread, NULL);
	(close_sem(philos->sems), unlink_sem());
	return (free(philos), 1);
}
