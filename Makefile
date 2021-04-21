# **************************************************************************** #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: Keita Hagiwara <al19136@shibaura-it.ac.jp>                            #
#                                                                              #
#    Created: 2021/04/14 23:01:18 by Keita Hagiwara                            #
#    Updated: 2021/04/14 23:01:18 by Keita Hagiwara                            #
#                                                                              #
# **************************************************************************** #

SRCS	= extstr.c read_file.c debug.c set_map.c ft_split.c check_map.c list_clear.c do_actions.c 
CC	= gcc
INC	= -I.
CFLAGS	= -Wall -Wextra -Werror -g -lm $(INC)
NAME	= al19136.scr
OBJS	= $(SRCS:.c=.o)
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY	:	clean fclean all re
