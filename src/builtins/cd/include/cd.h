/*
** cd.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/cd
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 20:56:31 2016 jonathan manassen
** Last update Fri Jun  3 20:57:42 2016 jonathan manassen
*/

#ifndef CD_H_
# define CD_H_

int	find_line_in_env(char*, char**);
int	check_str_space(char*, int);
int	check_builtin(char*, char*);

#endif /* !CD_H_ */
