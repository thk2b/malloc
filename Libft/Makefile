NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g

SRCDIR = srcs
INCLUDEDIR = includes

LINKED_LIST_SRCS = $(addprefix linked_list/, llist_new.c llist_free.c llist_push.c llist_shift.c llist_find.c llist_remove.c)
HASH_MAP_SRCS = $(addprefix hash_map/, hash_ascii.c hm_new.c hm_find.c hm_free.c hm_insert.c hm_new.c hm_remove.c hm_foreach.c hm_reduce.c)
QUEUE_SRCS = $(addprefix queue/, queue_new.c queue_free.c queue_add.c queue_pop.c)
PRIORITY_QUEUE_SRCS = $(addprefix priority_queue/, pq_new.c pq_free.c pq_add.c pq_get.c pq_pop.c)
ENV_SRCS = $(addprefix env/, ft_getenv.c ft_setenv.c ft_putenv.c ft_unsetenv.c)
STACK_SRCS = $(addprefix stack/, stack_new_node.c stack_free.c stack_push.c stack_pop.c stack_swap.c stack_rotate.c stack_rrotate.c stack_is_sorted.c)
CLIST_SRCS = $(addprefix clist/, clist_new.c clist_free.c clist_push.c clist_pop.c clist_rotate.c clist_rrotate.c clist_swap_next.c clist_is_sorted.c)
FT_PRINTF_SRCS = $(addprefix ft_printf/, parse_utils.c style.c parse.c linked_buffer.c convert_utils.c set_digits.c convert_num.c convert_str.c convert_wstr.c convert_percent.c convert.c get_len.c ft_asprintf.c ft_sprintf.c ft_printf.c)
SRCS = $(addprefix $(SRCDIR)/,\
	$(LINKED_LIST_SRCS)\
	$(HASH_MAP_SRCS)\
	$(QUEUE_SRCS)\
	$(PRIORITY_QUEUE_SRCS)\
	$(ENV_SRCS)\
	$(STACK_SRCS)\
	$(CLIST_SRCS)\
	$(FT_PRINTF_SRCS)\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strndup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_str_starts_with.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_strtrim.c\
	ft_strsplit.c\
	ft_strsplit_escape.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	ft_strvdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_itoa.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_strcjoin.c\
	ft_strvjoin.c\
	ft_btree_new.c\
	ft_btree_add.c\
	ft_btree_del.c\
	ft_btree_find.c\
	ft_btree_preorder.c\
	ft_btree_inorder.c\
	ft_btree_postorder.c\
	ft_btree_backpreorder.c\
	ft_btree_backinorder.c\
	ft_btree_backpostorder.c\
	get_next_line.c\
	ft_putstrv.c\
	ft_strv_len.c\
	ft_strv_add.c\
	ft_strv_dup.c\
	ft_strv_remove.c\
)

OBJS = $(SRCS:.c=.o)

%.o: %.c
	gcc -I$(INCLUDEDIR) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
