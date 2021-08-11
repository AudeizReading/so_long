CC=-gcc
ECHO=-echo
RM=-rm -rf
CFLAGS=-Wall -Werror -Wextra
CHEADERS= -I ./includes
LDFLAGS= -L ./lib
NAME=so_long
SRCS=
OBJ=$(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(ALL_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
