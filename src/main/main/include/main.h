/*
** main.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/main/main
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:52:22 2016 jonathan manassen
** Last update Sat Jun  4 17:12:35 2016 jonathan manassen
*/

#ifndef MAIN_H_
# define MAIN_H_

char	*get_next_line_ncurses(const int, char**, char**);
char	**launch_all_builtins(char*, char**, t_shrc*, t_prog*);
int	check_all_builtins(char*);
void	main_execute(char**, char*, int, t_prog*);
char	**main_execute_pipe(char**, char**, t_prog*, t_shrc*);
char	**get_tab(char*, char, t_prog*, t_shrc*);
void	save_history(char**);
int	test_invalid_null(char*);
char	*change_special_str(char*, char**, t_shrc*, int*);
int	launch_exit(char*, int, t_prog*);
void	init_structs(t_prog*, t_shrc*);
int	launch_exit(char*, int, t_prog*);
void	launch_cd(char*, char**, int*);
void	launch_env(char*, char**);
void	launch_echo(char*, t_prog*);
char	**launch_history(char*, t_shrc*, char**, t_prog*);
char	**launch_setenv(char*, char**, int, int*);
char	**launch_unsetenv(char*, char**, int*);
char	**launch_all_builtins(char*, char**, t_shrc*, t_prog*);
char	**launch_alias(char*, char**);
char	**launch_unalias(char*, char**, int, int*);
char	**launch_set(char*, char**, int, int*);
char	**launch_unset(char*, char**, int*);
int	find_line_in_env(char*, char**);
char	**start_exec(char*, char**, t_shrc*, t_prog*);
char	**realloc_history(char**, char*, int);
char	**get_env(char**);

#endif /* !MAIN_H_ */
