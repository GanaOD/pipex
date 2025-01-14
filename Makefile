# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/14 18:04:00 by go-donne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

all: $(NAME)

# First make libft
libft:
	@make -C libft/

# Then compile pipex and link with libft
$(NAME): libft
	$(CC) $(SRCS) -Llibft -lft -o $(NAME)

clean:
	@make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

re: fclean all
