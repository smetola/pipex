NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -ggdb3

SRC = pipex.c \
	init.c \
	exec.c \
	ft_split.c \
	utils.c \
	free_error.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all