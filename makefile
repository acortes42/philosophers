# **************************************************************************** #

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror -I -fsanitize=address  


# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_SRCS	=	./srcs/

DIR_OBJS	=	./compiled_objs/


# FILES #

SRCS			=	srcs/eat_or_die.c \
					srcs/utils.c \
					srcs/philo_creator.c \
					srcs/time_logic.c \
					srcs/main.c 

# COMPILED_SOURCES #

OBJS 		=	${SRCS: .c =.o}

NAME 		=	philo_one


# **************************************************************************** #

## RULES ##

all:			$(NAME)

# RULES #

$(NAME):		$(OBJS) includes/philosophers.h
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -c ${SRCS}
		@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) -lpthread -o ${NAME}

test:	
	@$(CC) $(CC_FLAGS) $(SRCS) -lpthread -o ${NAME} && ./philo_one 6 25 12 12 10
test_unsec:	
	@$(CC) $(SRCS) -lpthread -o ${NAME} && ./a.out 5 50000 3255 1000

# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED) '"$(DIR_OBJS)"' has been deleted.🗑️"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) *.out
				@echo "$(_RED) '"$(NAME)"' has been deleted.🗑️"

re:				fclean all

# PHONY #

.PHONY:			all clean fclean re test test_unsec
