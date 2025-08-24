#include "philosophers.h"


int	verify_input_args(char **argv)
{
	int	input;

	input = ft_atoi(argv[1]);
	if (input > 200 || input <= 0)
		printf("invalid number of philosophers\n");
	input = ft_atoi(argv[2]);
	if (input <= 0 || is_valid_digit(argv[2]) == 1)
		printf("invalid death time\n");
	input = ft_atoi(argv[3]);
	if (input <= 0 || is_valid_digit(argv[3]) == 1)
		printf("invalid feasting time");
	input = ft_atoi(argv[4]);
	if (input <= 0 || is_valid_digit(argv[4]) == 1)
		printf("invalid resting time");
	if (argv[5] && ((ft_atoi(argv[5])) < 0 || is_valid_digit(argv[5]) == 1))
		printf("invalid number of times philosophers must feast\n");
	return (0);
}