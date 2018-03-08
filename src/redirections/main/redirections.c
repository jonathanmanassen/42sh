/*
** redirections.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue Apr 12 19:48:49 2016 jonathan manassen
** Last update Sun Jun  5 21:36:10 2016 jonathan manassen
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "my.h"
#include "./include/redirections.h"

int	check_redirections_double_syntax(char *str, int *j)
{
  int	i;

  *j = 2;
  i = -1;
  while (str[++i] && str[i] == ' ');
  while (str[i] && str[i] != '<')
    i = i + 1;
  if (str[i] != '<')
    return (-1);
  while (str[++i] && str[i] == ' ');
  while (str[i] && str[i] != '>')
    i = i + 1;
  if (str[i] != '>')
    return (-1);
  if (str[i + 1] == '>')
    i = i + 1;
  if (str[i + 1] == '>')
    return (-1);
  if (check_str_space(str, i + 1) == 1)
    return (-1);
  return (0);
}

char	*get_goto_file(char *str, int i, int *k)
{
  char	*redirect;
  int	j;

  while (str[i] && str[i] != '>')
    i = i + 1;
  if (str[i + 1] == '>')
    {
      i = i + 1;
      *k = *k + 1;
    }
  while (str[++i] && str[i] == ' ');
  j = i;
  while (str[i] && str[i] != ' ')
    i = i + 1;
  ((redirect = malloc(sizeof(char*) * (i - j + 1))) == NULL) ? exit(0) : 0;
  i = -1;
  while (str[j] && str[j] != ' ')
    {
      redirect[++i] = str[j];
      str[j++] = ' ';
    }
  redirect[i + 1] = '\0';
  return (redirect);
}

char	**check_redirection_double(char *str, int *k, int i)
{
  int	j;
  char	**redirect;

  *k = 5;
  ((redirect = malloc(sizeof(char**) * 3)) == NULL) ? exit(0) : 0;
  while (str[++i] && str[i] == ' ');
  while (str[i] && str[i] != '<')
    i = i + 1;
  *k = (str[i + 1] && str[i + 1] == '<') ? *k + 2 : *k;
  i = (str[i + 1] && str[i + 1] == '<') ? i + 1 : i;
  while (str[++i] && str[i] == ' ');
  j = i;
  while (str[i] && str[i] != ' ' && str[i++] != '>');
  ((redirect[0] = malloc(sizeof(char*) * (i - j + 1))) == NULL) ? exit(0) : 0;
  i = -1;
  while (str[j] && str[j] != ' ' && str[j] != '>')
    {
      redirect[0][++i] = str[j];
      str[j++] = ' ';
    }
  redirect[0][i + 1] = '\0';
  redirect[1] = get_goto_file(str, j, k);
  redirect[2] = NULL;
  return (redirect);
}

void	get_fd_redirect(int fd[2], int *i, char *redirect,
			char **redirect_double)
{
  if (*i == 1)
    fd[0] = open(redirect, O_CREAT | O_RDWR | O_TRUNC, 0644);
  else if (*i == 2)
    fd[0] = open(redirect, O_CREAT | O_RDWR | O_APPEND, 0644);
  else if (*i == 3)
    fd[0] = open(redirect, O_RDONLY);
  else if (*i == 5 || *i == 6)
    fd[1] = open(redirect_double[0], O_RDONLY);
  if (*i == 5 || *i == 7)
    fd[0] = open(redirect_double[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
  if (*i == 6 || *i == 8)
    fd[0] = open(redirect_double[1], O_CREAT | O_RDWR | O_APPEND, 0644);
  if (fd[0] == -1  && (*i < 2 || *i > 4))
    exit(0);
  if ((fd[0] == -1 || (*i >= 5 && fd[1] == -1)) && *i != 4)
    *i = -1;
  if (fd[0] == -1 && *i != 4)
    my_printf("%s: No such file or directory.\n", redirect);
  if ((*i == 5 || *i == 6) && fd[1] == -1)
    my_printf("%s: No such file or directory.\n", redirect_double[0]);
}

void	check_redirections_execute(char *str, int *i, int fd[2], int *work)
{
  char	*redirect;
  char	**redirect_double;

  *i = 0;
  if (check_if_redirection(str) == -1)
    return;
  if (check_redirections_double_syntax(str, i) == -1)
    if (check_redirections_syntax(str, i) == -1)
      if (check_second_redirections_syntax(str, i) == -1)
	{
	  *i = -1;
	  *work = 1;
	  my_printf("Ambiguous output redirect.\n");
	  return;
	}
  if (*i == 0)
    redirect = check_redirections(str, i, -1, 0);
  else if (*i == 1)
    redirect = check_second_redirections(str, i);
  else
    redirect_double = check_redirection_double(str, i, -1);
  get_fd_redirect(fd, i , redirect, redirect_double);
  if (*i == 4 || *i == 7 || *i == 8)
    fd[1] = init_double_redirect(redirect, redirect_double[0], i);
}
