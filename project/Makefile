NAME = ft_malcolm
LIBFT = ./libft/libft.a
SRC =	./src/ft_malcolm.c \
		./src/parser.c \
		./src/parse_ip.c \
		./src/parse_mac.c \
		./src/mitm.c \
		./src/interface.c \
		./src/socket.c \
		./src/log_utils.c \
		./src/log.c \
		./src/packet.c \
		./src/utils.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
INCL = -I ./incl
R = rm -rf

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;36m
YELLOW = \033[1;33m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)compiling libft$(NC)"
	@make all -C ./libft
	@echo "$(BLUE)linking object files$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) ready$(NC)"

%.o: %.c
	@echo "$(BLUE)compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	@$(R) $(OBJS)
	@${MAKE} clean -C ./libft
	@echo "$(YELLOW)clean done.$(NC)"

fclean: clean
	@$(R) $(NAME)
	@${MAKE} fclean -C ./libft
	@echo "$(RED)full clean done.$(NC)"

re: fclean all
