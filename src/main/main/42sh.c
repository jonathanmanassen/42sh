/*
** minishell1.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue Jan 12 14:20:39 2016 jonathan manassen
** Last update Sun Jun  5 23:16:05 2016 jonathan manassen
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses/curses.h>
#include "my.h"
#include "./include/main.h"

static char	*prompt;

char	**launch_all_builtins(char *str, char **env,
			      t_shrc *shrc, t_prog *prog)
{
  if (str == NULL)
    return (env);
  if (check_all_builtins(str) == 0)
    prog->work = 0;
  if ((prog->quit = launch_exit(str, 0, prog)) == -1)
    write(2, "exit: Expression syntax\n", 24);
  if (prog->quit > 1)
    prog->work = 1;
  launch_cd(str, env, &prog->work);
  launch_env(str, env);
  launch_echo(str, prog);
  shrc->alias = launch_alias(str, shrc->alias);
  shrc->alias = launch_unalias(str, shrc->alias, 0, &prog->work);
  env = launch_history(str, shrc, env, prog);
  env = launch_setenv(str, env, 0, &prog->work);
  env = launch_unsetenv(str, env, &prog->work);
  shrc->set = launch_set(str, shrc->set, 0, &prog->work);
  shrc->set = launch_unset(str, shrc->set, &prog->work);
  return (env);
}

void	show_prompt(char **env)
{
  int	i;
  int	j;

  j = 5;
  prompt = NULL;
  if (isatty(0) == 1 && isatty(1) == 1)
    {
      if ((i = find_line_in_env("USER", env)) == -1)
	write(1, "\033[38;5;9m$> \033[0m", 16);
      else
	{
	  write(1, "\033[38;5;9m", 9);
	  j = j - 1;
	  if ((prompt = malloc(sizeof(char*) * (my_strlen(env[i]) - 4))) == NULL)
	    exit(0);
	  while (env[i][++j])
	    prompt[j - 5] = env[i][j];
	  prompt[j - 5] = '\0';
	  my_printf("%s", prompt);
	  write(1, "> \033[0m", 6);
	}
    }
}

char	*my_prompt(char **env, char **history, int work)
{
  int	i;
  char	*str;

  show_prompt(env);
  if (isatty(0) != 1 || isatty(1) != 1 ||
      (newterm(NULL, stdout, stdin)) == NULL)
    str = get_next_line(0);
  else
    str = get_next_line_ncurses(0, env, history);
  if (str == NULL)
    {
      save_history(history);
      if (isatty(0) == 1 && isatty(1) == 1)
	my_printf("exit\n");
      endwin();
      exit(work);
    }
  endwin();
  i = -1;
  while (str[++i])
    str[i] = (str[i] == '\t') ? ' ' : str[i];
  return (str);
}

void	block_sigint()
{
  if (prompt == NULL)
    write(1, "\n\033[38;5;9m$> \033[0m", 17);
  else
    {
      write(1, "\n\033[38;5;9m", 10);
      my_printf("%s", prompt);
      write(1, "> \033[0m", 6);
    }
}

int		main(int argc, char **argv, char **env)
{
  char		*str;
  char		**my_env;
  t_shrc	shrc;
  t_prog	prog;

  (void)argc;
  (void)argv;
  signal(SIGINT, block_sigint);
  my_env = get_env(env);
  init_structs(&prog, &shrc);
  while (1)
    {
      str = my_prompt(my_env, shrc.history, prog.work);
      my_env = start_exec(str, my_env, &shrc, &prog);
      free(prompt);
    }
}
