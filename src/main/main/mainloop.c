/*
** mainloop.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri May 20 21:59:18 2016 jonathan manassen
** Last update Sun Jun  5 23:18:59 2016 jonathan manassen
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "./include/main.h"

extern int	leave;

char	**launch_pipes(t_prog *prog, char **env, t_shrc *shrc, int i)
{
  if (i == 0 || (prog->value[i - 1] == 1 && prog->work == 1) ||
      (prog->value[i - 1] == 2 && prog->work == 0) ||
      prog->value[i - 1] == 0)
    if (prog->p != NULL && prog->p[0] != NULL)
      {
	prog->c = '0';
	if (prog->p[0] != NULL && prog->p[1] == NULL)
	  {
	    if (check_all_builtins(prog->p[0]) == 1)
	      main_execute(env, prog->p[0], i, prog);
	    else
	      env = launch_all_builtins(prog->p[0], env, shrc, prog);
	  }
	else
	  env = main_execute_pipe(env, prog->p, prog, shrc);
      }
  return (env);
}

char		**mainloop(char *str, char **env, t_shrc *shrc, t_prog *prog)
{
  char		**tab;
  int		i;

  if ((tab = get_tab(str, ';', prog, shrc)) != NULL)
    {
      i = -1;
      while (tab[++i] != NULL &&
	     (i == 0 || prog->value[i - 1] != 1 || prog->work == 1 ||
	      prog->quit == 0))
	{
	  prog->quit = (prog->quit >= 0) ? 0 : prog->quit;
	  if (tab[i] != NULL)
	    {
	      prog->p = get_tab(tab[i], '|', prog, shrc);
	      env = launch_pipes(prog, env, shrc, i);
	    }
	}
    }
  if (prog->quit >= 0)
    {
      (isatty(0) == 1 && isatty(1) == 1) ? my_printf("exit\n") : 0;
      save_history(shrc->history);
      (prog->quit == 0) ? exit(prog->work) : exit(prog->quit);
    }
  return (env);
}

char	**start_exec(char *str, char **env, t_shrc *shrc, t_prog *prog)
{
  if (test_invalid_null(str) == 1)
    {
      prog->work = 1;
      my_printf("Invalid null command.\n");
    }
  else if (str[0] != '\0' && str[0] != '|')
    {
      if ((str = change_special_str(str, env, shrc, &prog->work)) != NULL)
	env = mainloop(str, env, shrc, prog);
      shrc->history = realloc_history(shrc->history, str, 6);
    }
  return (env);
}
