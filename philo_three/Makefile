# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdrake <gdrake@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 01:52:51 by gdrake            #+#    #+#              #
#    Updated: 2020/11/22 17:05:47 by gdrake           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c libft_utils.c init_args.c philo_utils.c parse_n_check_args.c life_cycle.c write_logs.c monitoring.c forks_take_put.c ft_atoi_re.c ft_itoa_re.c init_semaphores.c init_n_kill_philo_processes.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

INCLUDES = philo_one.h

$(NAME): $(OBJS) 
	gcc  ${CFLAGS} $(OBJS) -pthread -o $(NAME)
	@echo "\n༼ つ ◕_◕  philo_one is compiled! ༼ つ ◕_◕ "

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

%.o: %.c
	gcc ${CFLAGS} $^ -o $@ -c

FOR_NORM = . 

norme:
	norminette $(FOR_NORM)

.PHONY:	all clean fclean re norme