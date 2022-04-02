# **************************************************************************** #

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror #-g -fsanitize=thread


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
					srcs/main.c \
					srcs/aux.c \
					srcs/utils_main.c

# COMPILED_SOURCES #

OBJS 		=	${SRCS: .c =.o}

NAME 		=	philo


# **************************************************************************** #

## RULES ##

all:			$(NAME)

# RULES #

$(NAME):		$(OBJS) includes/philosophers.h
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -c ${SRCS}
		@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) -lpthread -o ${NAME}

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

.PHONY:			all clean fclean re
