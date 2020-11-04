NAME = philo_one

CFLAGS = #-Wall -Wextra #-Werror

SRCS = main.c libft_utils.c init_args.c philo_utils.c parse_n_check_args.c life_cycle.c write_logs.c monitoring.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

INCLUDES = philo_one.h

$(NAME): $(OBJS) 
	@gcc  ${CFLAGS} $(OBJS) -pthread -o $(NAME)
	@echo "༼ つ ◕_◕  philo_one is compiled! ༼ つ ◕_◕ "

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re:	fclean $(NAME)

%.o: %.c
	@gcc ${CFLAGS} $^ -o $@ -c

FOR_NORM = . 

norme:
	norminette $(FOR_NORM)

.PHONY:	all clean fclean re norme