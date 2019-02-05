ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CC = gcc

# DEFINES = $(addprefix -D, LOG)
CC_FLAGS = -Wall -Wextra -Werror -Wpedantic -Ofast
# CC_FLAGS += -g -fsanitize=undefined
CC_SO_FLAGS = -fPIC

LIB = libft/libft.a
INC = $(addprefix -I, libft/includes inc src src/area src/area_list src/block src/free_block src/free_list src/lib)
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
	$(addprefix area/, area.c area__count.c area__coalesce_free_block.c area__coalesce_block.c area__split_free_block.c area__split_block.c)\
	$(addprefix area_list/, area_list.c area_list__insert.c)\
	$(addprefix block/, block.c)\
	$(addprefix free_block/, free_block.c)\
	$(addprefix free_list/, free_list.c free_list__find_first_fit.c free_list__find_first_fit_coalesce.c free_list__insert_address_ordered.c free_list__insert_local_address_ordered.c)\
	$(addprefix lib/, hexdump.c lib.c)\
)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIB):
	make -C libft

$(NAME): $(OBJ) $(LIB)
	$(COMPILE) $(LIB) -shared -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LINK_NAME)

$(OBJ): %.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) $(DEFINES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LINK_NAME)
	make fclean -C libft

re: fclean all
