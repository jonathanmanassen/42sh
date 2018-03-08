/*
** echo.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/builtins/cd
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 20:56:17 2016 jonathan manassen
** Last update Fri Jun  3 21:06:13 2016 jonathan manassen
*/

#ifndef ECHO_H_
# define ECHO_H_

void	dup_redirection(int, int*, t_prog*);
void	launch_echo(char*, t_prog*);
int	check_builtin(char*, char*);
char	*pars_simple_cote_str(char*);
void	check_redirections_execute(char*, int*, int*);

#endif /* !ECHO_H_ */
