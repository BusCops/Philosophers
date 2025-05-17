/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:35:56 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/17 14:28:02 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args_error(char *s)
{
	printf("______%s______\n", s);
	printf("to use this program only give these arguments\n");
	printf("         ->number_of_philosophers<-          \n");
	printf("               ->time_to_die<-               \n");
	printf("               ->time_to_eat<-               \n");
	printf("              ->time_to_sleep<-              \n");
	printf("_________________|optional|__________________\n");
	printf("->number_of_times_each_philosopher_must_eat<-\n");
	exit (1);
}

int	check_valid_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (bc_is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	arg_checker(int	ac, char **av)
{
	(void)av;
	if (ac < 5)
		print_args_error("too few argument for a philosopher");
	if (ac > 6)
		print_args_error("too much argument for a philosopher");
	if (check_valid_args(av))
		print_args_error("_______only enter number pls_______");
	if (!bc_strlen(av[1]) || !bc_strlen(av[2]) || !bc_strlen(av[3]) || !bc_strlen(av[4]))
		print_args_error("_____pls give a valid argument_____");
}

void	initialise_program(t_philo *pg, char **av)
{
	pg->philo_n = bc_atoi(av[1]);
	pg->t_die = bc_atoi(av[2]);
	pg->t_eat = bc_atoi(av[3]);
	pg->t_sleep = bc_atoi(av[4]);
	if (!av[5] || !bc_strlen(av[5]))
		pg->n_t_eat = 0;
	else
		pg->n_t_eat = bc_atoi(av[5]);
	if (!pg->philo_n)
		print_args_error("philosopher number can't be zero");
}
