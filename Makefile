RED=\033[1;31m
GRE=\033[1;32m
YEL=\033[1;33m
BLU=\033[1;34m
MAG=\033[1;35m
CYA=\033[1;36m
NO_COL=\033[0m
CC=-gcc
ECHO=-echo
RM=-rm -rf
MAKE=make
CFLAGS=-Wall -Werror -Wextra
CHEADERS= -I ./includes
LDFLAGS= -L ./lib/libft -lft
ALL_FLAGS= $(CHEADERS) $(CFLAGS)
NAME=so_long
LIBFT_PATH=./lib/libft
SRCS=$(addprefix srcs/, $(addsuffix .c, \
	 main \
	 ))\
	 $(addprefix srcs/ft_, $(addsuffix .c, \
	 main \
	 ))
OBJ=$(SRCS:.c=.o)

.PHONY: all clean fclean re test debug

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) libft
	@$(ECHO) "$(GRE)"
	$(CC) $(LDFLAGS) $^ -o $@
	@$(ECHO) "$(NO_COL)"
	$(MAKE) libftclean

libft:
	@$(ECHO) "$(YEL)"
	$(MAKE) -C $(LIBFT_PATH) all
	@$(ECHO) "$(NO_COL)"

test: $(NAME)
	./$(NAME)
	$(MAKE) fclean
	
debug: $(OBJ)
	$(CC) -g $(LDFLAGS) $^ -o $@
	valgrind ./$@
	$(MAKE) clean
	$(RM) $@ debug.dSYM

%.o: %.c
	@$(ECHO) "$(GRE)"
	$(CC) $(ALL_FLAGS) -c $< -o $@
	@$(ECHO) "$(NO_COL)"

clean:
	@$(ECHO) "$(RED)"
	$(RM) $(OBJ)
	@$(ECHO) "$(NO_COL)"

libftclean: clean
	@$(ECHO) "$(RED)"
	$(RM) $(LIBFT_PATH)/libft.a
	@$(ECHO) "$(NO_COL)"

fclean: libftclean
	@$(ECHO) "$(RED)"
	$(RM) $(NAME)
	@$(ECHO) "$(NO_COL)"

re: fclean all
