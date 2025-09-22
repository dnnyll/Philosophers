NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = include
SRCS =	srcs/cleanup.c \
		srcs/initialize.c \
		srcs/main.c \
		srcs/monitor.c \
		srcs/parser.c \
		srcs/print.c \
		srcs/routine_actions.c \
		srcs/routine.c \
		srcs/threads.c \
		srcs/time.c \
		srcs/utils.c

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