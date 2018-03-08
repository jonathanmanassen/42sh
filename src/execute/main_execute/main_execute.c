/*
** main_execute.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri May 20 23:03:12 2016 jonathan manassen
** Last update Sun Jun  5 22:42:08 2016 jonathan manassen
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>
#include "my.h"
#include "./include/main_execute.h"

extern int	leave;

char	**run_execve2(char **path, char **exe, char *tmp, int i)
{
  int	size;
  int	k;
  int	j;

  j = -1;
  while (exe[0][++j])
    tmp[j] = exe[0][j];
  tmp[j] = '\0';
  size = my_strlen(tmp) + my_strlen(path[i]) + 1;
  if ((exe[0] = malloc(sizeof(char*) * size)) == NULL)
    exit(0);
  j = -1;
  if (tmp[0] != '/')
    while (path[i][++j])
      exe[0][j] = path[i][j];
  if (j != -1)
    exe[0][j] = '/';
  k = -1;
  while (++k <= (my_strlen(tmp) + 1))
    exe[0][++j] = tmp[k];
  return (exe);
}

int	run_execve(char **path, char **exe, char **env)
{
  int	i;
  int	j;
  char	*tmp;

  i = -1;
  j = 1;
  path = get_basic_path(exe, env, &j, path);
  if (j == 1)
    {
      while (path[++i])
	{
	  if ((tmp = malloc(sizeof(char*) * (my_strlen(exe[0]) + 1))) == NULL)
	    exit(0);
	  exe = run_execve2(path, exe, tmp, i);
	  if (execve(exe[0], exe, env) == -1)
	    {
	      j = -1;
	      while (++j <= (my_strlen(tmp) + 1))
		exe[0][j] = tmp[j];
	      exe[0][j] = '\0';
	      free(tmp);
	    }
	}
    }
  return (-1);
}

void	close_fd_check_work(t_prog *prog, int fd[2], int i, pid_t pid)
{
  close(prog->fd2[1]);
  if (i > 0)
    close(fd[0]);
  if (i > 4)
    close(fd[1]);
  if (i == 4 || i >= 7)
    remove(".tmp");
  if ((read(prog->fd2[0], &prog->c, 1)) == -1)
    {
      prog->work = 1;
      return;
    }
  if (prog->c == '1' || i == -1)
    prog->work = 1;
  else
    prog->work = 0;
  check_signal(pid, &prog->work);
}

void	main_execute(char **my_env, char *str, int i, t_prog *prog)
{
  char	**exe;
  char	**path;
  pid_t	pid;
  int	fd[2];

  if ((pipe(prog->fd2)) == -1)
    return;
  path = search_path(my_env);
  check_redirections_execute(str, &i, fd, &prog->work);
  str = clear_redirects(str);
  if ((exe = get_command(str)) != NULL && exe[0] != NULL && i != -1)
    {
      ((pid = fork()) == -1) ? exit(0) : 0;
      if (pid != 0)
	wait(&pid);
      else
	{
	  dup_redirection(i, fd, prog);
	  if (run_execve(path, exe, my_env) == -1)
	    write_error(exe[0], prog->fd2[1]);
	  free_functions(exe, path, 1);
	}
      free_functions(exe, path, 0);
    }
  close_fd_check_work(prog, fd, i, pid);
}
