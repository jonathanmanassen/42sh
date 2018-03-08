/*
** main.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/redirections/main
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 22:02:42 2016 jonathan manassen
** Last update Sun Jun  5 21:36:22 2016 jonathan manassen
*/

#ifndef REDIRECTION_H_
# define REDIRECTIONS_H_

int	check_str_space(char*, int);
int	check_if_redirection(char*);
int	check_redirections_syntax(char*, int*);
int	check_second_redirections_syntax(char*, int*);
char	*check_redirections(char*, int*, int, int);
char	*check_second_redirections(char*, int*);
int	check_builtin(char*, char*);
int	init_double_redirect(char*, char*, int*);

#endif /* !REDIRECTIONS_H_ */
