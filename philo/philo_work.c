/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:11:05 by abenzaho          #+#    #+#             */
/*   Updated: 2025/06/03 17:48:52 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (get_time() < philo->pg->start_time)
		usleep(250);
	update_elapsed_time(philo->pg);
	philo->last_meal = philo->pg->time_stamp;
	print_action(philo, "has taken a fork");
	return (NULL);
}

void	wich_fork_start_with(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		update_elapsed_time(philo->pg);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		update_elapsed_time(philo->pg);
		print_action(philo, "has taken a fork");
	}
}

void	philo_routine(t_philo *philo)
{
	update_elapsed_time(philo->pg);
	wich_fork_start_with(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->pg->time);
	philo->last_meal = philo->pg->time_stamp;
	pthread_mutex_unlock(&philo->pg->time);
	cus_usleep(philo->pg->t_eat, philo);
	update_elapsed_time(philo->pg);
	pthread_mutex_lock(philo->meals_n);
	philo->n_eat++;
	pthread_mutex_unlock(philo->meals_n);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_action(philo, "is sleeping");
	cus_usleep(philo->pg->t_sleep, philo);
	print_action(philo, "is thinking");
	if (philo->pg->t_eat > philo->pg->t_sleep)
	{
		cus_usleep(philo->pg->t_eat - philo->pg->t_sleep, philo);
	}
	if (philo->pg->philo_n % 2 != 0)
		usleep(500);
}

void	*even_philo(void *ptr)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)ptr;
	dead = 0;
	while (get_time() < philo->pg->start_time)
		usleep(250);
	if (philo->id % 2 != 0 && philo->pg->philo_n % 2 == 0)
		usleep(1000);
	else if (philo->id % 2 == 0 && philo->pg->philo_n % 2 != 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->pg->dl);
		dead = philo->pg->is_dead;
		pthread_mutex_unlock(&philo->pg->dl);
		if (dead)
			return (NULL);
		philo_routine(philo);
		pthread_mutex_lock(philo->meals_n);
		if (philo->n_eat == philo->pg->n_t_eat && philo->pg->n_t_eat != 0)
			return (pthread_mutex_unlock(philo->meals_n), NULL);
		pthread_mutex_unlock(philo->meals_n);
	}
	return (NULL);
}
