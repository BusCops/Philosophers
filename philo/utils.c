/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:41:08 by abenzaho          #+#    #+#             */
/*   Updated: 2025/06/03 14:05:35 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	update_elapsed_time(t_mp *pg)
{
	pthread_mutex_lock(&pg->time);
	pg->time_stamp = get_time() - pg->start_time;
	pthread_mutex_unlock(&pg->time);
}

void	print_action(t_philo *philo, char *action)
{
	update_elapsed_time(philo->pg);
	pthread_mutex_lock(&philo->pg->time);
	pthread_mutex_lock(&philo->pg->dl);
	if (!philo->pg->is_dead)
		printf("%ld %d %s\n", philo->pg->time_stamp, philo->id, action);
	pthread_mutex_unlock(&philo->pg->dl);
	pthread_mutex_unlock(&philo->pg->time);
}

void	free_all(t_philo *philos, t_mp *pg)
{
	int	i;

	i = 0;
	if (philos)
		free(philos);
	if (pg->forks)
	{
		while (i < pg->philo_n)
		{
			free(pg->forks[i]);
			i++;
		}
		free(pg->forks);
	}
	i = 0;
	if (pg->meals)
	{
		while (i < pg->philo_n)
		{
			free(pg->meals[i]);
			i++;
		}
		free(pg->meals);
	}
}

void	cus_usleep(long time, t_philo *philo)
{
	long	curr;

	if (time == 0)
		return ;
	curr = get_time();
	while (get_time() - curr < time)
	{
		pthread_mutex_lock(&philo->pg->dl);
		if (philo->pg->is_dead)
		{
			pthread_mutex_unlock(&philo->pg->dl);
			return ;
		}
		pthread_mutex_unlock(&philo->pg->dl);
		usleep(500);
	}
}
