/*
** set.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/set
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:14:36 2016 jonathan manassen
** Last update Fri Jun  3 21:16:56 2016 jonathan manassen
*/

#ifndef SET_H_
# define SET_H_

char	**my_realloc_double_array(char**, int, int);
int	check_builtin(char*, char*);
int	check_str_space(char*, int);
int	check_alphanumeric(char*, int, char*, char);
int	find_line_in_set(char*, char**);
char	**launch_unalias(char*, char**, int, int*);
void	show_alias(char**);

#endif /* !SET_H_ */
