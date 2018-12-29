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

LIB = $(addprefix lib/,\
	strlen.c\
	putstr.c\
	putnbr.c\
	putaddr.c\
)

CORE = $(addprefix core/,\
	area.c\
	block.c\
	zone.c\
)
SRC = $(addprefix srcs/,\
	$(LIB)\
	$(CORE)\
	free.c\
	malloc.c\
	calloc.c\
	realloc.c\
	show_alloc_mem.c\
)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILE) -shared -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LINK_NAME)

#$(LIB):
#	make -C $(LIBDIR)

$(OBJ): %.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
#	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME) $(LINK_NAME)
#	make fclean -C $(LIBDIR)

re: fclean all
