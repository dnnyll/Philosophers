/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:13:00 by daniefe2          #+#    #+#             */
/*   Updated: 2025/09/18 16:59:00 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	verify_input_args(char **argv)
{
	int	i;
	int	value;

	i = 1;
	while (argv[i])
	{
		if (is_valid_digit(argv[i]))
		{
			printf("Invalid characters in argument %d\n", i);
			return (1);
		}
		value = ft_atoi(argv[i]);
		if (i == 1 && (value <= 0 || value > 200))
			return (printf("Invalid number of philosophers\n"), 1);
		if (i == 2 && value <= 0)
			return (printf("Invalid death time\n"), 1);
		if (i == 3 && value <= 0)
			return (printf("Invalid feasting time\n"), 1);
		if (i == 4 && value <= 0)
			return (printf("Invalid resting time\n"), 1);
		if (i == 5 && value < 0)
			return (printf("Invalid number of meals\n"), 1);
		i++;
	}
	return (0);
}
