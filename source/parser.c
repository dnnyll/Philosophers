/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:13:00 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/25 12:13:01 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int verify_input_args(char **argv)
{
	int	args[5];

	args[0] = ft_atoi(argv[1]); // number of philosophers
	args[1] = ft_atoi(argv[2]); // death time
	args[2] = ft_atoi(argv[3]); // feasting time
	args[3] = ft_atoi(argv[4]); // resting time
	if (argv[5])
		args[4] = ft_atoi(argv[5]);
	else
		args[4] = -1;
	if (args[0] <= 0 || args[0] > 200)
		printf("invalid number of philosophers\n");
	if (args[1] <= 0 || is_valid_digit(argv[2]) == 1)
		printf("invalid death time\n");
	if (args[2] <= 0 || is_valid_digit(argv[3]) == 1)
		printf("invalid feasting time\n");
	if (args[3] <= 0 || is_valid_digit(argv[4]) == 1)
		printf("invalid resting time\n");
	if (argv[5] && (args[4] < 0 || is_valid_digit(argv[5]) == 1))
		printf("invalid number of times philosophers must feast\n");
	return (0);
}
