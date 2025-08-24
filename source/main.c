#include "philosophers.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 4 || argc > 5)
	{
		printf("incorrect number of arguments.\n");
		return (-1);
	}
	verify_input_args(argv);
	return (0);
}