/*
** env.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/env
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:02:37 2016 jonathan manassen
** Last update Fri Jun  3 21:06:34 2016 jonathan manassen
*/

#ifndef ENV_H_
# define ENV_H_

char	**check_realloc(char**, int);
char	**malloc_env(char**, char*, int, int);
int	check_str_space(char*, int);
int	check_builtin(char*, char*);
int	check_correct_change(char*, int, char**, int);
char	*get_line_name(char*, int, int);
int	find_line_in_env(char*, char**);
void	launch_env(char*, char**);
char	**my_realloc_double_array(char**, int, int);

#endif /* !MY_H_ */
