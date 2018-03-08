/*
** get_tab.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Apr  7 15:08:02 2016 jonathan manassen
** Last update Sat Jun  4 17:36:37 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/get_execute.h"

void	get_prog_value(t_prog *prog, t_coord *p, char *str, char c)
{
  p->k = p->k + 1;
  if (c == ';')
    while (str[p->i] && str[p->i] != c && (str[p->i] != '|' ||
					   str[p->i + 1] != '|') &&
	   (str[p->i] != '&' || str[p->i + 1] != '&'))
      p->i = p->i + 1;
  else
    while (str[p->i] && str[p->i] != c)
      p->i = p->i + 1;
  if (c == ';' && (str[p->i] == c || str[p->i] == '&' || str[p->i] == '|'))
    {
      if (str[p->i] == ';')
	prog->value[p->k] = 0;
      if (str[p->i] == '|' && str[p->i + 1] == '|')
	prog->value[p->k] = 1;
      if (str[p->i] == '&' && str[p->i + 1] == '&')
	prog->value[p->k] = 2;
    }
}

char		**get_tabs(char **path, char *str, t_prog *prog, t_shrc *shrc)
{
  int		j;
  int		l;
  t_coord	p;
  char		c;

  c = prog->c;
  j = p.i = 0;
  p.k = -1;
  while (str[p.i])
    {
      l = 0;
      while (str[p.i] && (str[p.i] == c ||
			(c == ';' && (str[p.i] == '&' || str[p.i] == '|'))))
	j = ++p.i;
      get_prog_value(prog, &p, str, c);
      if ((path[p.k] = malloc(sizeof(char*) * (p.i - j + 1))) == NULL)
	exit(0);
      while (j < p.i)
	path[p.k][l++] = str[j++];
      path[p.k][l] = '\0';
      if (c == '|' &&
	  (path[p.k] = launch_turn_alias(shrc, path[p.k], prog)) == NULL)
	return (NULL);
    }
  return (path);
}

char	**get_tab(char *str, char c, t_prog *prog, t_shrc *shrc)
{
  int	i;
  int	j;
  char	**path;

  i = -1;
  j = 0;
  if (str[0] == '\0')
    return (NULL);
  while (str[++i])
    if ((str[i] == c || (c == ';' && ((str[i] == '&' && str[i + 1] == '&') ||
				      (str[i] == '|' && str[i + 1] == '|')))) &&
	str[i + 1] != c && str[i + 1] != '\0')
      j = j + 1;
  if (str[0] == c || (str[0] == '&' && c == ';'))
    j = j - 1;
  if ((path = malloc(sizeof(char**) * (j + 2))) == NULL)
    exit(0);
  if (c == ';' && j >= 0)
    if ((prog->value = malloc(sizeof(int*) * j)) == NULL)
      exit(0);
  prog->c = c;
  if ((path = get_tabs(path, str, prog, shrc)) == NULL)
    return (NULL);
  path[j + 1] = NULL;
  return (path);
}
