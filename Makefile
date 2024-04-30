OS              := $(shell uname)
NAME            = minishell
CC              = cc
SRCDIR          = src
SRC             = array_utils.c \
                  builtin.c \
                  builtin_utils.c \
                  cmd_utils.c \
                  env.c \
                  env_utils.c \
                  error.c \
                  error_handling.c \
                  error_handling_utils.c \
                  exec.c \
                  expansion.c \
                  expansion_utils.c \
                  file_redirection.c \
                  free.c \
                  history.c \
                  history2.c \
                  list_utils.c \
                  main.c \
                  node_utils.c \
                  parser.c \
                  parser_utils.c \
                  pipe.c \
                  redirection_file_utils.c \
                  signals.c \
                  stack.c \
                  tokenizer.c \
                  tokenizer_utils.c \
                  tokenizer_utils2.c \
                  utils.c
OBJDIR          = obj
OBJS            = $(SRC:%.c=$(OBJDIR)/%.o)
LIBFTPATH       = libft
LIBFT           = $(LIBFTPATH)/libft.a
CFLAGS          = -g -Wall -Werror -Wextra

# Conditional Readline paths for macOS
ifeq ($(OS),Darwin)
    READLINE_PATH = $(shell brew --prefix readline)
    INC_DIR       = -I$(READLINE_PATH)/include
    LIB_DIR       = -L$(READLINE_PATH)/lib
else
    INC_DIR       =
    LIB_DIR       =
endif

# Generic rule for .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFTPATH) all

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LIB_DIR) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(LIBFTPATH)/*.o
	rm -rf $(LIBFTPATH)/*.a

re: fclean all

run: all
	./$(NAME)

