/*
** pipe.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Apr  7 15:25:18 2016 jonathan manassen
** Last update Sun Jun  5 22:03:40 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>
#include "my.h"
#include "./include/misc.h"

extern int	leave;

char	*get_str_from_tab(char **tab)
{
  int	i;
  int	j;
  int	k;
  char	*str;

  k = 0;
  j = 0;
  i = -1;
  while (tab[++i])
    j += my_strlen(tab[i]) + 1;
  if ((str = malloc(sizeof(char*) * (j + 1))) == NULL)
    exit(0);
  i = -1;
  while (tab[++i])
    {
      str[k++] = ' ';
      j = 0;
      while (tab[i][j])
	str[k++] = tab[i][j++];
    }
  str[k] = '\0';
  return (str);
}

void	check_env_function(char **str, t_prog *prog, char **env, t_shrc *shrc)
{
  if (check_builtin(str[0], "env") != -1)
    launch_env("env", env);
  else if (check_builtin(str[0], "echo") != -1)
    launch_echo(get_str_from_tab(str), prog);
  else if (run_execve(prog->path, str, env) == -1)
    {
      launch_all_builtins(get_str_from_tab(str), env, shrc, prog);
      write_error(str[0], prog->error[1]);
    }
}

char	***init_exe(char **str)
{
  char	***exe;
  int	i;
  int	j;

  i = 0;
  while (str[i] != NULL)
    i = i + 1;
  if ((exe = malloc(sizeof(char***) * (i + 1))) == NULL)
    exit(0);
  i = -1;
  j = -1;
  while (str[++i] != NULL)
    exe[++j] = get_command(str[i]);
  exe[j + 1] = NULL;
  return (exe);
}

char	init_pipe(t_prog *prog, char **str, int fd[2], char **my_env)
{
  int	i;
  int	j;

  i = -1;
  j = 0;
  while (str[++i] && j == 0)
    if (check_if_redirection(str[i]) == 1)
      {
	if (find_redirect_pipe(str, prog) == -1 || prog->fd == -1)
	  {
	    prog->work = 1;
	    return ('1');
	  }
	j = 1;
      }
  if (pipe(fd) == -1 || pipe(prog->error) == -1)
    return ('1');
  if ((find_line_in_env("PATH", my_env)) == -1)
    prog->path = NULL;
  else
    prog->path = get_path(my_env[find_line_in_env("PATH", my_env)]);
  i = -1;
  while (str[++i])
    str[i] = clear_redirects(str[i]);
  return ('0');
}

char		**main_execute_pipe(char **my_env, char **str,
				    t_prog *prog, t_shrc *shrc)
{
  char		***exe;
  pid_t		pid;
  char		c;

  c = '0';
  if ((prog->pfd = malloc(sizeof(char*) * 2)) == NULL)
    exit(0);
  prog->k = 0;
  if ((c = init_pipe(prog, str, prog->pfd, my_env)) == '1')
    return (my_env);
  exe = init_exe(str);
  prog->i = 0;
  ((pid = fork()) < 0) ? exit(0) : 0;
  if (pid == 0)
    recursive(exe, prog, my_env, shrc);
  else
    wait(&pid);
  close(prog->error[1]);
  if ((read(prog->error[0], &c, 1)) == -1)
    return (my_env);
  close(prog->error[0]);
  prog->work = (c == '1') ? 1 : 0;
  free(prog->pfd);
  return (my_env);
}
