ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -Wpedantic #-Ofast
CC_FLAGS += -g
CC_SO_FLAGS = -fPIC

INC = -I inc -I src/srea -I src/area_list src/block -I src/free_block -I src/free_list -I src/lib
COMPILE = $(CC) $(CC_FLAGS) $(INC)

SRC = $(addprefix src/,\
	dump_mem.c\
	free.c\
	globals.c\
	malloc.c\
	realloc.c\
	show_alloc_mem.c\
	$(addprefix area/, )\
	$(addprefix area_list/, )\
	$(addprefix block/, )\
	$(addprefix free_block/, )\
	$(addprefix free_list/, )\
)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILE) -shared -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LINK_NAME)

$(OBJ): %.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) -DMALLOC_LOG -DMALLOC_DEBUG -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LINK_NAME)

re: fclean all
