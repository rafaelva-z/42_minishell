# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 16:21:22 by scosta-j          #+#    #+#              #
#    Updated: 2024/01/07 16:54:28 by fda-estr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address 
LIBFLAGS	=	-L$(LIBFT_PATH) -lft -lreadline 
RM			=	/bin/rm -f
INCLUDES	=	./include
LIBFT_PATH	=	./lib/libft/
LIBFT		=	$(LIBFT_PATH)libft.a
SRCS		=	$(addprefix ./src/,		\
				main.c					\
				signals.c				\
				prompt_cleaner.c		\
				quote_check.c			\
				redir_add_spaces.c		\
				redir_check.c			\
				redir_utils.c			\
				tokenizer.c				\
				utils.c					\
				utils2.c				\
				here_doc.c				\
				destroyer.c				\
				error_handling.c		\
				$(addprefix built-ins/, \
				cd.c					\
				echo.c					\
				env.c					\
				exit.c					\
				export.c				\
				export_sort.c 			\
				pwd.c					\
				unset.c					\
				)						\
				$(addprefix structs/,	\
				commands.c				\
				env.c					\
				env2.c					\
				redirections.c			\
				)						\
				$(addprefix executor/,	\
				executor.c				\
				exec_utils.c		\
				path_handeling.c		\
				redirections.c			\
				)						\
				)						\
				
CYAN		=	\033[96m
RESET		=	\033[0m
TAG			=	$(CYAN)[$(NAME)]$(RESET)

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	@echo "$(TAG) Making Program"
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_FOLDER) readline.supp

fclean: clean
	@echo "$(TAG) Full clean." 
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all
	@echo "$(TAG) Recompiling."
	@make -C $(LIBFT_PATH) re

run: re
	@clear
	./$(NAME)

readline.supp:
	wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

runvg: re readline.supp
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re