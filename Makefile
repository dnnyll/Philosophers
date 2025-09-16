NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = include
SRCS =	source/initialize.c \
		source/main.c \
		source/memory_utils.c \
		source/monitor.c \
		source/parser.c \
		source/print.c \
		source/routine_actions.c \
		source/routine.c \
		source/threads.c \
		source/time.c \
		source/utils.c

OBJS = $(SRCS:.c=.o)
%.o: %.c
		$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
		rm -rf $(OBJS)
fclean: clean
		rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re