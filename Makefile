ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

LIBDIR = libft
LIB = libft.a

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror
#CC_FLAGS += -g -fsanitize=address
CC_SO_FLAGS = -fPIC

INC = -I $(LIBDIR)/includes -I ./inc
COMPILE = $(CC) $(CC_FLAGS) $(INC)

CORE = $(addprefix core/,)
SRC = $(addprefix srcs/,\
	malloc.c\
	free.c\
	realloc.c\
	$(CORE)\
)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@echo building $(NAME)
	$(COMPILE) -shared $(INC) -o $(NAME) $(OBJ)
	ln -sf $(NAME) $(LINK_NAME)

$(LIB):
	make -C $(LIBDIR)

%.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME) $(LINK_NAME)
	make fclean -C $(LIBDIR)

re: fclean all
