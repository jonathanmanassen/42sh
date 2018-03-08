##
## Makefile for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
## 
## Made by jonathan manassen
## Login   <manass_j@epitech.net>
## 
## Started on  Tue Jan 12 15:16:03 2016 jonathan manassen
## Last update Sun Jun  5 19:28:10 2016 jonathan manassen
##

SRCLIB	= ./lib/my/my_putchar.c\
	./lib/my/my_fputchar.c\
	./lib/my/my_putstr.c\
	./lib/my/my_fputstr.c\
	./lib/my/my_strlen.c\
	./lib/my/my_strlen_double_array.c\
	./lib/my/my_getnbr.c\
	./lib/my/my_putnbr.c\
	./lib/my/my_fputnbr.c\
	./lib/my/my_printf.c\
	./lib/my/my_fprintf.c\
	./lib/my/my_printf2.c

NAMELIB	= libmy.a

SRC	= ./src/gnl/gnl/usual_get_next_line.c\
	./src/gnl/gnl_ncurses/get_next_line.c\
	./src/gnl/gnl_ncurses/misc_get_next_line.c\
	./src/gnl/gnl_ncurses/backspace.c\
	./src/gnl/gnl_ncurses/is_printable.c\
	./src/gnl/complete/complete_word.c\
	./src/gnl/complete/stat.c\
	./src/gnl/complete/get_name_opendir.c\
	./src/gnl/complete/ls.c\
	./src/gnl/complete/get_data_complete.c\
	./src/builtins/alias/alias.c\
	./src/builtins/alias/use_alias.c\
	./src/builtins/alias/check_alias.c\
	./src/builtins/alias/change_alias.c\
	./src/builtins/alias/show_alias.c\
	./src/builtins/alias/unalias.c\
	./src/builtins/history/history.c\
	./src/builtins/history/history_builtin.c\
	./src/builtins/history/get_time_history.c\
	./src/builtins/history/get_history.c\
	./src/builtins/env/find_env.c\
	./src/builtins/env/change_env.c\
	./src/builtins/env/change_env_check.c\
	./src/builtins/env/delete_env.c\
	./src/builtins/echo/simple_cote.c\
	./src/builtins/echo/echo.c\
	./src/builtins/set/set.c\
	./src/builtins/cd/cd.c\
	./src/builtins/main/builtins.c\
	./src/redirections/check/check_redirections.c\
	./src/redirections/main/double_redirect.c\
	./src/redirections/main/redirections.c\
	./src/redirections/main/redirect_pipe.c\
	./src/execute/get_execute/get_args.c\
	./src/execute/get_execute/get_tab.c\
	./src/execute/misc/pipe.c\
	./src/execute/misc/execute.c\
	./src/execute/main_execute/recursive_pipe.c\
	./src/execute/main_execute/main_execute.c\
	./src/main/misc/free.c\
	./src/main/misc/error.c\
	./src/main/misc/init.c\
	./src/main/change_string/change_str.c\
	./src/main/main/mainloop.c\
	./src/main/main/42sh.c

NAME	= 42sh

CC	= gcc -g

RM	= rm -f

LIB	= -lmy -L./lib/ -lncurses

CFLAGS	+= -W -Wall -Werror -I./include

OBJ	= $(SRC:.c=.o)

OBJLIB	= $(SRCLIB:.c=.o)

all : $(NAMELIB) $(NAME)

$(NAMELIB) : $(OBJLIB)
	ar rc $(NAMELIB) $(OBJLIB)
	ranlib $(NAMELIB)
	mv $(NAMELIB) lib

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)

clean :
	$(RM) $(OBJ) $(OBJLIB)

fclean : clean
	$(RM) $(NAME) lib/$(NAMELIB)

re : fclean all

.PHONY : all clean fclean re
