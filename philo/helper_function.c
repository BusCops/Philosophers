/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:13:39 by abenzaho          #+#    #+#             */
/*   Updated: 2025/05/17 14:02:39 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	bc_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	bc_atoi(const char *s)
{
	long long	n;
	int			i;
	
	i = 0;
	n = 0;
	while (s[i])
	{
		n = (n * 10) + (s[i] - '0');
		if (n > INT_MAX)
			print_args_error("______thats a large number_______");
		i++;
	}
	return (n);
}

size_t	bc_strlen(const char *string)
{
	size_t	len;

	len = 0;
	if (!string)
		return 0;
	while (string[len])
		len++;
	return (len);
}
