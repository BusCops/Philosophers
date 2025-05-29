/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:41:08 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/29 14:51:33 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handle(const char *s, t_mp *pg, t_philo *philos)
{
	write(2, "philo : ", 8);
	write(2, s, bc_strlen(s));
	write(2, "\n", 1);
	free_all(philos, pg);
	exit(1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	update_elapsed_time(t_mp *pg)
{
	long	t_now;	

	t_now = get_time();
	pg->time_stamp = t_now - pg->start_time;
}

void	print_action(t_philo *philo, char *action)
{
	update_elapsed_time(philo->pg);
	pthread_mutex_lock(&philo->pg->dl);
	if (!philo->pg->is_dead)
		printf("%ld %d %s\n", philo->pg->time_stamp, philo->id, action);
	pthread_mutex_unlock(&philo->pg->dl);
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
}

void	cus_usleep(long time)
{
	usleep(time * 1000);
}