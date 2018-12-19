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

all: $(NAME) create_link

$(NAME): $(LIB) $(OBJ)
	@echo building $(name)
	$(CC) -shared $(OBJ) -o $(NAME)

$(LIB):
	make -C $(LIBDIR)

%.o: %.c
	$(COMPILE) $(CC_SO_FLAGS) $(LIBDIR)/$(LIB) -c $< -o $@

create_link:
	ln -sf $(NAME) $(LINK_NAME)

inject:
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES=libft_malloc.so
	export DYLD_FORCE_FLAT_NAMESPACE=1

clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME) $(LINK_NAME)
	make fclean -C $(LIBDIR)

re: fclean all
