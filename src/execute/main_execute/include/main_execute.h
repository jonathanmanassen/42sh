/*
** main_execute.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/execute/main_execute
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:21:10 2016 jonathan manassen
** Last update Sun Jun  5 20:15:12 2016 jonathan manassen
*/

#ifndef MAIN_EXECUTE_H_
# define MAIN_EXECUTE_H_

void	recursive(char***, t_prog*, char**, t_shrc*);
void	close_fd(int*, int*, int, t_prog*);
void	launch_redirect_pipe(t_prog*);
void	check_env_function(char**, t_prog*, char**, t_shrc*);
char	**get_basic_path(char**, char**, int*, char**);
void	check_signal(int, int*);
char	**search_path(char**);
void	check_redirections_execute(char*, int*, int*, int*);
char	*clear_redirects(char*);
char	**get_command(char*);
void	dup_redirection(int, int*, t_prog*);
void	write_error(char*, int);
void	free_functions(char**, char**, int);

#endif /* !MAIN_EXECUTE_H_ */
