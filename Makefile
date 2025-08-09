#Variables
NAME= pipex
LIBFT= libft/libft.a
AR= ar rcs

#project files
SRC= arg_validation.c commands_validation.c pipex.c utils.c
OBJ_DIR= obj
OBJ= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

#commands and flags
CC= cc
CFLAGS= -Wall -Wextra -Werror
INCLUDES= -I. -I./libft

define LOADING_BAR_COMP
	@printf "\033[0;32mCompiling pipex: ["
	@for i in `seq 1 20`; do \
		printf "█"; \
		sleep 0.05; \
	done; \
	printf "] ✔️\033[0m\n\n"
endef

#paths
LIBFT_DIR= libft
INCLUDES= -I. -I$(LIBFT_DIR)

#rules

all: $(NAME)

$(LIBFT):
	@(MAKE) -C libft

$(NAME): $(OBJ)
		@$(MAKE) -C $(LIBFT_DIR) --silent
		$(call LOADING_BAR_COMP)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent

re: fclean all

.PHONY: all clean fclean re
