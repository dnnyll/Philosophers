#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*
┌───────────┬───────────────┬─────────────────────────────────┐
│ Color     │ ANSI Code      │ Meaning / Use                  │
├───────────┼───────────────┼─────────────────────────────────┤
│ WHITE     │ \033[0;37m    │ Normal text / philosophers full │
│ RED       │ \033[0;31m    │ Dead / error                    │
│ GREEN     │ \033[0;32m    │ Thinking / ok                   │
│ YELLOW    │ \033[0;33m    │ Fork taken / warning            │
│ BLUE      │ \033[0;34m    │ Sleeping / info                 │
│ MAGENTA   │ \033[0;35m    │ Eating / active                 │
├───────────┴───────────────┴─────────────────────────────────┤
│ How it works:                                               │
│ 1. \033[ starts the escape sequence                         │
│ 2. 0 = normal, 1 = bold/bright, etc.                        │
│ 3. 30-37 = foreground colors (black-white)                  │
│ 4. m ends the code and applies it                           │
│ 5. Reset color with \033[0m after printing                  │
└─────────────────────────────────────────────────────────────┘
*/

//	parser.c
int	verify_input_args(char **input);

//	utils.c
int	is_valid_digit(char *arg);
int	ft_atoi(const char *str);

#endif
