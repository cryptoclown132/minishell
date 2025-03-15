
NAME = minishell

SRC = ${shell find ./parser -name "*.c" && find ./lexer_expander -name "*.c" && find ./builtins -name "*.c" && echo *.c}

OBJ = $(patsubst %.c, %.o, $(SRC))

HEADER = minishell.h

LIBFT = ./libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include 

LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	(cd libft; make)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT)  -o $(NAME) 

clean:
	(cd libft; make clean)
	rm -f $(OBJ)

fclean: clean
	(cd libft; make fclean)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
