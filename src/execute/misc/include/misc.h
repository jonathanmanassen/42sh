/*
** misc.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/execute/misc
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:26:01 2016 jonathan manassen
** Last update Fri Jun  3 21:41:28 2016 jonathan manassen
*/

#ifndef MISC_H_
# define MISC_H_

char	**launch_all_builtins(char*, char**, t_shrc*, t_prog*);
void	write_erro(char*, int);
char	**get_command(char*);
int	check_if_redirection(char*);
int	find_line_in_env(char*, char**);
char	**get_path(char*);
char	*clear_redirects(char*);
void	recursive(char***, t_prog*, char**, t_shrc*);
int	check_builtin(char*, char*);
void	launch_env(char*, char**);
void	launch_echo(char*, t_prog*);
int	run_execve(char**, char**, char**);
void	write_error(char*, int);
int	find_redirect_pipe(char**, t_prog*);

#endif /* !MISC_H_ */
