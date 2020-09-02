# **************************************************************************** #

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror


# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_SRCS	=	./srcs/

DIR_OBJS	=	./compiled_objs/


# FILES #

SRCS			=	srcs/eat_or_die.c \
					srcs/utils.c \
					srcs/philo_creator.c \
					srcs/anti_leaks.c \
					srcs/main.c 

# COMPILED_SOURCES #

OBJS 		=	${SRCS: .c =.o}

NAME 		=	philo_one


# **************************************************************************** #

## RULES ##

all:			$(NAME)

# RULES #

$(NAME):		$(OBJS) includes/philosophers.h
		#@mkdir -p ${DIR_OBJS}
		#@${CC} ${CFLAGS} -c ${SRCS} -lpthread
		#@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) -lpthread -o ${NAME}

test:	
	@$(CC) $(CC_FLAGS) $(SRCS) -lpthread && ./a.out 4 8000 500 1000 9
test_unsec:	
	@$(CC) $(SRCS) -lpthread && ./a.out 4 50000 3255 1000

# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED) '"$(DIR_OBJS)"' has been deleted.🗑️"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(_RED) '"$(NAME)"' has been deleted.🗑️"

re:				fclean all

# PHONY #

.PHONY:			all clean fclean re test test_unsec
