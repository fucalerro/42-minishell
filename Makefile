OS              := $(shell uname)
NAME            = minishell
CC              = cc
AR              = ar -rc
SRCDIR          = src
SRC             = $(wildcard $(SRCDIR)/*.c)
OBJDIR          = obj
OBJ             = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
LIBFTPATH       = libft
LIBFT           = $(LIBFTPATH)/libft.a
CFLAGS          = # -Wall -Werror -Wextra

# Conditional Readline paths for macOS
ifeq ($(OS),Darwin)
	READLINE_PATH   = $(shell which brew | sed 's|/bin/brew$$||')
    INC_DIR         = -I$(READLINE_PATH)/opt/readline/include
    LIB_DIR         = -L$(READLINE_PATH)/opt/readline/lib
else
    INC_DIR         =
    LIB_DIR         =
endif

# Generic rule for .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -g -c $< -o $@

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTPATH) all

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(LIB_DIR) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf *.dSYM
	rm -rf $(LIBFTPATH)/*.o
	rm -rf $(LIBFTPATH)/*.a

re: fclean all
test :
	echo "$(OS)"  $(LIB_DIR)

run: all
	./$(NAME)
