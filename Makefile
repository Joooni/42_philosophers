# -*- MakeFile -*-

NAME = philo

# -*- Compiler -*-
GCC = gcc
FLAGS = -Wall -Wextra -Werror -Wuninitialized -pthread -ggdb3 -O3
SAN_FLAG = -fsanitize=thread

# -*- Includes -*-
SRC_PATH	= src
BONUS_PATH	= bonus
OBJ_PATH	= obj
INCL		= incl

# -*- Source Files -*-
SRC_FILES	=	philosophers.c \
				init.c \
				utils.c \
				utils_philo.c \
				checks_philo.c \
				threading_philo.c \


# -*- Objects -*-
SRCS	=	$(addprefix $(SRC_PATH)/,$(SRC_FILES))

all: $(NAME)

$(NAME): $(SRCS)
	$(GCC) $(FLAGS) $^ -o $(NAME)

sanitize: $(SRCS)
	$(GCC) $(FLAGS) $(SAN_FLAG) $^ -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: tmp, lib, re, fclean, clean