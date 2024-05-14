#############################################
###		 			CONFIG		          ###
#############################################

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -g $(INCLUDES)

MKDIR			= mkdir -p

SOURCES_DIR		= src
SOURCES			= $(SOURCES_DIR)/main.c $(SOURCES_DIR)/check_for_builtins.c $(SOURCES_DIR)/exact_match.c $(SOURCES_DIR)/ft_strlen.c $(SOURCES_DIR)/exit_handler.c 
OBJ				= $(OBJ_DIR)/main.o $(OBJ_DIR)/check_for_builtins.o $(OBJ_DIR)/exact_match.o $(OBJ_DIR)/ft_strlen.o $(OBJ_DIR)/exit_handler.o
OBJ_DIR			= obj

INCLUDES		= -I ./includes

TOTAL_FILES := $(words $(wildcard $(SOURCES_DIR)/*.c))

COMPILE_COUNT = 0

#############################################
###					COLORS			      ###
#############################################

RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
RESET_COLOR		= \033[0m
MOVEUP			= \033[F
RESET			= \e[2K\r

#############################################
###		 			RULES	      	      ###
#############################################

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a -lreadline
	@echo "$(RESET)$(GREEN)Compiled $(NAME)$(RESET_COLOR)"

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval COMPILE_COUNT=$(shell echo $$(($(COMPILE_COUNT)+1))))
	@echo -n "$(RESET)[$(YELLOW)$$(($(COMPILE_COUNT)*100/$(TOTAL_FILES)))%] Compiling minishell"

libft/libft.a:
	@make -sC libft

clean:
	@make fclean -sC libft
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Removed the object files from minishell$(RESET_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Removed $(NAME) and the object files$(RESET_COLOR)"

re:
	@make -s fclean
	@make -s

.PHONY:	all clean fclean re
