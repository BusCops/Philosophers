/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:11:05 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/29 15:52:35 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *ptr)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)ptr;
	while (1)
	{
		i = 0;
		update_elapsed_time(philo->pg);
		while (i < philo->pg->philo_n)
		{
			if ((philo[i].pg->time_stamp - philo[i].last_meal) >= philo[i].pg->t_die)
			{
				pthread_mutex_lock(&philo[i].pg->dl);
				philo[i].pg->is_dead = 1;
				pthread_mutex_unlock(&philo[i].pg->dl);
				update_elapsed_time(philo->pg);
				printf("%ld %d is dead\n", philo[i].pg->time_stamp, philo[i].id);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	*single_philo(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	update_elapsed_time(philo->pg);
	philo->last_meal = philo->pg->time_stamp;
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork");
	while (1)
	{
		update_elapsed_time(philo->pg);
		if ((philo->pg->time_stamp - philo->last_meal) >= philo->pg->t_die)
			break ;
	}
	print_action(philo, "died");
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	update_elapsed_time(philo->pg);
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	update_elapsed_time(philo->pg);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	cus_usleep(philo->pg->t_eat);
	philo->last_meal = philo->pg->time_stamp;
	philo->n_eat++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_action(philo, "is sleeping");
	cus_usleep(philo->pg->t_sleep);
	print_action(philo, "is thinking");
}

void	*even_philo(void *ptr)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)ptr;
	dead = 0;
	if (philo->id % 2 == 0)
			usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->pg->dl);
		dead = philo->pg->is_dead;
		pthread_mutex_unlock(&philo->pg->dl);
		if (dead)
			return (NULL);
		philo_routine(philo);
		if (philo->n_eat == philo->pg->n_t_eat && philo->pg->n_t_eat != 0)
			return (NULL);
	}
	return (NULL);
}
