/*
** misc.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/main/misc
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:58:27 2016 jonathan manassen
** Last update Sun Jun  5 22:38:44 2016 jonathan manassen
*/

#ifndef MISC_H_
# define MISC_H_

int	check_letter(char*, char);
int	check_all_builtins(char*);
int	check_builtin(char*, char*);
int	check_str_space(char*, int);
char	**init_history(void);
char	**init_alias(int);

#endif /* !MISC_H_ */
