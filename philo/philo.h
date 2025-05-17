/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:36:03 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/17 14:28:34 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_philo
{
	int	philo_n;
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	n_t_eat;
}	t_philo;

//helper function
int		bc_is_digit(int c);
int		bc_atoi(const char *s);
size_t	bc_strlen(const char *string);

//program arg check function
void	print_args_error(char *s);
void	arg_checker(int	ac, char **av);
void	initialise_program(t_philo *pg, char **av);

//program function

#endif