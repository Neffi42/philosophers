/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:32:22 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 15:17:26 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_var(t_var *var, int val)
{
	if (pthread_mutex_init(&var->mutex, NULL))
		return (error(FCT, "pthread_mutex_init"), 1);
	var->content = val;
	return (0);
}

void	incr_var(t_var *var)
{
	pthread_mutex_lock(&(var->mutex));
	var->content++;
	pthread_mutex_unlock(&(var->mutex));
}

void	set_var(t_var *var, int val)
{
	pthread_mutex_lock(&(var->mutex));
	var->content = val;
	pthread_mutex_unlock(&(var->mutex));
}

int	get_var(t_var *var)
{
	int	i;

	pthread_mutex_lock(&(var->mutex));
	i = var->content;
	pthread_mutex_unlock(&(var->mutex));
	return (i);
}
