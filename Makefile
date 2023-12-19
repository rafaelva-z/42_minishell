# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 16:21:22 by scosta-j          #+#    #+#              #
#    Updated: 2023/12/05 17:24:14 by rvaz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address 
LIBFLAGS	=	-L$(LIBFT_PATH) -lft -lreadline 
RM			=	/bin/rm -f
INCLUDES	=	./include
LIBFT_PATH	=	./lib/libft/
LIBFT		=	$(LIBFT_PATH)libft.a
SRCS		=	./src/main.c  ./src/_env.c ./src/signals.c  ./src/utils.c \
				./src/built-ins/pwd.c ./src/built-ins/cd.c  ./src/built-ins/echo.c \
				./src/built-ins/env.c  ./src/built-ins/exit.c  ./src/built-ins/export.c \
				./src/built-ins/unset.c \
				./src/prompt_cleaner.c
				
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

fclean: clean
	@echo "$(TAG) Full clean." 
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all
	@echo "$(TAG) Recompiling."
	@make -C $(LIBFT_PATH) re

.PHONY: all clean fclean re