# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echatela <echatela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 12:02:13 by echatela          #+#    #+#              #
#    Updated: 2025/09/23 17:01:47 by echatela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
RLFLAGS     =	-lreadline -lncurses

SRCS		=	src/main.c \
				$(TERMDIR)prompt.c $(TERMDIR)readline.c \
				$(LEXPARSDIR)ms_lexer_parser.c \
				$(LEXDIR)ms_lexer.c $(LEXDIR)utils_lexer.c $(LEXDIR)utils_tok.c $(LEXDIR)ms_lex_read.c $(LEXDIR)tokvec.c $(LEXDIR)tokvec_push.c \
				$(EXITDIR)ms_cleanup.c $(EXITDIR)ms_error.c $(EXITDIR)ms_fatal.c $(EXITDIR)fill.c \
				$(UTILSDIR)join_and_free.c $(UTILSDIR)realloc_array.c \
				$(ENVPASS)ft_create_envp_list.c $(ENVPASS)ft_new_envp.c \
				src/built_in/ms_cd.c src/built_in/ms_echo.c src/built_in/ms_env.c src/built_in/ms_exit.c src/built_in/ms_export.c src/built_in/ms_pwd.c src/built_in/ms_unset.c \
# 				src/process/ms_process.c 

TERMDIR		=	src/term/
LEXPARSDIR	=	src/lexer_parser/
LEXDIR		=	src/lexer_parser/lexer/
EXITDIR		=	src/exit/
ENVPASS		=	src/env/
UTILSDIR	=	src/utils/
OBJDIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I includes -I $(LIBFT_DIR)

all:	$(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RLFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean 

fclean:		clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
re: fclean all

.PHONY:		all clean fclean re debug