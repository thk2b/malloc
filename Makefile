ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

LIBDIR = libft
LIB = libft.a

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror
CC_FLAGS += -g
CC_SO_FLAGS = -fPIC

INC = -I $(LIBDIR)/includes -I inc
COMPILE = $(CC) $(CC_FLAGS) $(INC)

CORE = $(addprefix core/,\
	zones.c\
	find_block.c\
	block.c\
	get_free_block.c\
	get_zone.c\
	page.c\
)
SRC = $(addprefix srcs/,\
	$(CORE)\
	malloc.c\
	free.c\
	realloc.c\
	show_alloc_mem.c\
)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(COMPILE) -shared -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LINK_NAME)

$(LIB):
#	make -C $(LIBDIR)

$(OBJ): %.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME) $(LINK_NAME)
	make fclean -C $(LIBDIR)

re: fclean all
