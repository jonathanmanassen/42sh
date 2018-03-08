/*
** gnl_ncurses.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/gnl/gnl_ncurses
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:43:12 2016 jonathan manassen
** Last update Sat Jun  4 19:48:55 2016 jonathan manassen
*/

#ifndef GNL_NCURSES_H_
# define GNL_NCURSES_H_

void	launch_write_ls(char**, char*, int, int);
char	**no_options(int, char*);
int	count_files(char*);
char	*auto_complete(char*, int*, int*);
char	*my_realloc_ncurses(char*);
char	*get_history(char*, char**, int*, int*);
char	*init_get_next_line(int*, int*);
int	is_printable(char, char**, int*);
char	*put_char_in_str(char*, char, int*, int*);
void	show_get_next_line(char*, char**, int, int*);
char	*change_str_for_stat(char*, char*, int);
void	check_if_slash_space(char*, int*, int*);
void	show_prompt(char**);
char	*backspace(char, char*, int*, int*);
char	*alt_backspaces(char*, int*, int*);

#endif /* !GNL_NCURSES_H_ */
