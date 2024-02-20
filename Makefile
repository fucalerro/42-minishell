OS 				:=	$(shell uname)

NAME			=	minishell

CC				=	cc
AR				=	ar -rc
SRCD	IR			=	src
SRC				=	$(wildcard $(SRCDIR)/*.c)
OBJDIR			=	obj
OBJ				=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
LIBFTPATH		=	libft
LIBFT			=	$(LIBFTPATH)/libft.a
CFLAGS			=	# -Wall -Werror -Wextra

# Generic rule for .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -g -c $< -o $@

all: $(NAME)

$(LIBFT):
					make -C $(LIBFTPATH) all

$(NAME): 			$(LIBFT) $(OBJ)
					$(CC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
					rm -f $(OBJ)

fclean: clean
					rm -f $(NAME)
					rm -rf *.dSYM
					rm -rf $(LIBFTPATH)/*.o
					rm -rf $(LIBFTPATH)/*.a

re: fclean all
