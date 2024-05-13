#############################################
###		 			CONFIG		          ###
#############################################

NAME			= minishell

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -g $(INCLUDES) 

MKDIR			= mkdir -p

SOURCES_DIR		= src
SOURCES			= $(SOURCES_DIR)/main.c $(SOURCES_DIR)/check_for_builtins.c $(SOURCES_DIR)/exact_match.c $(SOURCES_DIR)/ft_strlen.c $(SOURCES_DIR)/exit_handler.c $(SOURCES_DIR)/env_builtin.c $(SOURCES_DIR)/cd_builtin.c $(SOURCES_DIR)/pwd_builtin.c $(SOURCES_DIR)/trim_whitespaces.c
OBJ				= $(OBJ_DIR)/main.o $(OBJ_DIR)/check_for_builtins.o $(OBJ_DIR)/exact_match.o $(OBJ_DIR)/ft_strlen.o $(OBJ_DIR)/exit_handler.o $(OBJ_DIR)/env_builtin.o $(OBJ_DIR)/cd_builtin.o $(OBJ_DIR)/pwd_builtin.o $(OBJ_DIR)/trim_whitespaces.o
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

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline 
	@echo "$(RESET)$(GREEN)Compiled $(NAME)$(RESET_COLOR)"

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval COMPILE_COUNT=$(shell echo $$(($(COMPILE_COUNT)+1))))
	@echo -n "$(RESET)$(YELLOW)Compiling minishell $$(($(COMPILE_COUNT)*100/$(TOTAL_FILES)))%"

clean:

	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Removed the object files from minishell$(RESET_COLOR)"

fclean:

	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo "$(GREEN)Removed $(NAME) and the object files$(RESET_COLOR)"

re:
	@make -s fclean
	@make -s

.PHONY:	all clean fclean re
