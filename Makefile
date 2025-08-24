NAME = philoshopers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = include
SRCS =	source/main.c \
		source/parser.c \
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