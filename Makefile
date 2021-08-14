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
LDFLAGS= -L ./lib/libft -lft -L ./lib/gnl -lgnl
ALL_FLAGS= $(CHEADERS) $(CFLAGS)
NAME=so_long
LIBFT_PATH=./lib/libft
GNL_PATH=./lib/gnl
SRCS=$(addprefix srcs/, $(addsuffix .c, \
	 main\
	 ))\
	 $(addprefix srcs/ft_, $(addsuffix .c, \
	 basic_error\
	 map_errors\
	 check_map\
	 get_map\
	 init_line\
	 map_size\
	 last_line\
	 map_addback\
	 map_delone\
	 map_clear\
	 print_map\
	 ))
OBJ=$(SRCS:.c=.o)

.PHONY: all clean fclean re test debug libft gnl

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) libft
	@$(MAKE) gnl
	@$(ECHO) "$(GRE)"
	$(CC) $(LDFLAGS) $^ -o $@
	@$(ECHO) "$(NO_COL)"
	@$(MAKE) clean
	@$(MAKE) libftclean
	@$(MAKE) gnlclean

libft:
	@$(ECHO) "$(YEL)"
	$(MAKE) -C $(LIBFT_PATH) all
	@$(ECHO) "$(NO_COL)"

gnl:
	@$(ECHO) "$(MAG)"
	$(MAKE) -C $(GNL_PATH) all
	@$(ECHO) "$(NO_COL)"

test: $(NAME)
	./$(NAME) maps/13x5_valid_map.ber
	@$(MAKE) fclean
	
debug: $(OBJ)
	@$(MAKE) libft
	@$(MAKE) gnl
	@$(ECHO) "$(BLU)"
	$(CC) -g $(LDFLAGS) $^ -o $@
	@$(ECHO) "$(NO_COL)"
	valgrind ./$@ maps/13x5_valid_map.ber
	@$(MAKE) clean
	@$(MAKE) libftclean
	@$(MAKE) gnlclean
	@$(ECHO) "$(RED)"
	$(RM) $@ debug.dSYM
	@$(ECHO) "$(NO_COL)"

debug-full: $(OBJ)
	@$(MAKE) libft
	@$(MAKE) gnl
	@$(ECHO) "$(BLU)"
	$(CC) -g $(LDFLAGS) $^ -o $@
	@$(ECHO) "$(NO_COL)"
	valgrind --leak-check=full ./$@ maps/13x5_valid_map.ber
	@$(MAKE) clean
	@$(MAKE) libftclean
	@$(MAKE) gnlclean
	@$(ECHO) "$(RED)"
	$(RM) $@ debug-full.dSYM
	@$(ECHO) "$(NO_COL)"

%.o: %.c
	@$(ECHO) "$(GRE)"
	$(CC) $(ALL_FLAGS) -c $< -o $@
	@$(ECHO) "$(NO_COL)"

clean:
	@$(ECHO) "$(RED)"
	$(RM) $(OBJ)
	@$(ECHO) "$(NO_COL)"

libftclean: 
	@$(ECHO) "$(RED)"
	$(RM) $(LIBFT_PATH)/libft.a
	@$(ECHO) "$(NO_COL)"

gnlclean:
	@$(ECHO) "$(RED)"
	$(RM) $(GNL_PATH)/libgnl.a
	@$(ECHO) "$(NO_COL)"

fclean: clean libftclean gnlclean
	@$(ECHO) "$(RED)"
	$(RM) $(NAME)
	@$(ECHO) "$(NO_COL)"

re: fclean all
