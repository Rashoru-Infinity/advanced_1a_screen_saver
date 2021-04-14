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

SRCS	=	extstr.c read_file.c
CC		= gcc
INC		= -I$(shell pwd)
CFLAGS	= -Wall -Wextra -Werror $(INC)
NAME	= al19136.scr
OBJS	= $(SRCS:.c=.o)
RM		= rm -f

all		:	$(NAME)

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
