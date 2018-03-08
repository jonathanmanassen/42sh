/*
** history.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/history
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:08:02 2016 jonathan manassen
** Last update Sun Jun  5 22:27:21 2016 jonathan manassen
*/

#ifndef HISTORY_H_
# define HISTORY_H_

int	check_letter(char*, char);
char	**my_realloc_double_array(char**, int, int);
char	*put_time_in_history(char*, int*, int);
int	check_builtin(char*, char*);
char	**start_exec(char*, char**, t_shrc*, t_prog*);
char	*get_str(int);
char	*get_hist(char*, int);

#endif /* !HISTORY_H_ */
