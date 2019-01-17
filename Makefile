ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -Wpedantic -fsanitize=undefined #-Ofast
CC_FLAGS += -g
CC_SO_FLAGS = -fPIC

INC = -I inc -I src -I src/area -I src/area_list -I src/block -I src/free_block -I src/free_list -I src/lib
COMPILE = $(CC) $(CC_FLAGS) $(INC)

SRC = $(addprefix src/,\
	hexdump_mem.c\
	errors.c\
	free.c\
	globals.c\
	log.c\
	malloc.c\
	realloc.c\
	show_alloc_mem.c\
	$(addprefix area/, area.c)\
	$(addprefix area_list/, area_list.c area_list__insert.c)\
	$(addprefix block/, block.c)\
	$(addprefix free_block/, )\
	$(addprefix free_list/, )\
	$(addprefix lib/, hexdump.c lib.c)\
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
