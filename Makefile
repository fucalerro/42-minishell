OS              :=  $(shell uname)

NAME            =   minishell

CC              =   cc
AR              =   ar -rc
SRCDIR          =   src
SRC             =   $(wildcard $(SRCDIR)/*.c)
OBJDIR          =   obj
OBJ             =   $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
LIBFTPATH       =   libft
LIBFT           =   $(LIBFTPATH)/libft.a
CFLAGS          =   # -Wall -Werror -Wextra
TESTDIR         =   tests
TESTSRC         =   $(wildcard $(TESTDIR)/*.c)
TESTOBJ         =   $(patsubst $(TESTDIR)/%.c, $(TESTDIR)/%.o, $(TESTSRC))
TESTNAME        =   test_bin

# Generic rule for .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -g -c $< -o $@

all: $(NAME)

$(LIBFT):
				make -C $(LIBFTPATH) all

$(NAME):         $(LIBFT) $(OBJ)
				$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean:
				rm -f $(OBJ)
				rm -f $(TESTOBJ)

fclean: clean
				rm -f $(NAME)
				rm -rf *.dSYM
				rm -rf $(LIBFTPATH)/*.o
				rm -rf $(LIBFTPATH)/*.a
				rm -f $(TESTNAME)

re: fclean all

# Updated test rule
test: $(TESTOBJ)
				$(CC) -DUNIT_TESTS -o $(TESTNAME) $(filter-out obj/main.o,$(OBJ)) $(TESTOBJ) -lreadline $(LIBFT)
				./$(TESTNAME)

# Rule to compile test objects. Assumes tests may need to link with project objects or libraries.
$(TESTDIR)/%.o: $(TESTDIR)/%.c
				$(CC) $(CFLAGS) -g -c $< -o $@
