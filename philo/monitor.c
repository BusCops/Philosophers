/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:48:16 by abenzaho          #+#    #+#             */
/*   Updated: 2025/06/03 17:50:56 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ckeck_meals(t_philo *philo)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < philo->pg->philo_n)
	{
		pthread_mutex_lock(philo[i].meals_n);
		if (philo[i].n_eat == philo[i].pg->n_t_eat && philo[i].pg->n_t_eat != 0)
			c++;
		pthread_mutex_unlock(philo[i].meals_n);
		i++;
	}
	if (c == i)
		return (1);
	return (0);
}

void	philo_is_dead(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->pg->time);
	pthread_mutex_lock(&philo[i].pg->dl);
	philo[i].pg->is_dead = 1;
	pthread_mutex_unlock(&philo[i].pg->dl);
	update_elapsed_time(philo->pg);
	pthread_mutex_lock(&philo->pg->time);
	printf("%ld %d is dead\n", philo[i].pg->time_stamp, philo[i].id);
	pthread_mutex_unlock(&philo->pg->time);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	while (1)
	{
		i = 0;
		if (ckeck_meals(philo))
			return (NULL);
		while (i < philo->pg->philo_n)
		{
			update_elapsed_time(philo->pg);
			pthread_mutex_lock(&philo->pg->time);
			if ((philo[i].pg->time_stamp
					- philo[i].last_meal) > philo[i].pg->t_die)
			{
				philo_is_dead(philo, i);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->pg->time);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
