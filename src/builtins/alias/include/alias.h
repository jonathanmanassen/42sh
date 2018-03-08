/*
** alias.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/alias
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 20:41:05 2016 jonathan manassen
** Last update Sat Jun  4 19:09:26 2016 jonathan manassen
*/

#ifndef ALIAS_H_
# define ALIAS_H_

char	*turn_str_into_alias(char**, char*, int*, int);
char	*take_away_alias(char*);
char	*alias_short(char*, char);
char	*alias_long(char*, char);
char	**realloc_alias(char**, char*);
int	check_all_alias(int*, int, int);
int	*realloc_int_tab(int*, int);
int	check_alias_cmd(char*, char);
char	**my_realloc_double_array(char**, int, int);
int	check_str_space(char*, int);
void	change_alias_file(char**);
int	check_builtin(char*, char*);
void	show_alias(char**);
int	check_change_alias(char*, char**);
char	**change_alias(char**, char*, int);
char	*my_lowcase(char*);
char	**swap_str(char**, int, int);
char	**get_name(char*, int);
char	**delete_env_line(char**, int, int, int);

#endif /* !ALIAS_H_ */
