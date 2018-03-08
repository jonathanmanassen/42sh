/*
** check_redirections.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon Apr 11 16:50:06 2016 jonathan manassen
** Last update Sun Jun  5 20:59:46 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"

char	*check_redirections(char *str, int *k, int i, int j)
{
  char	*redirect;

  while (str[++i] && str[i] != '>' && str[i] != '<');
  *k = (str[i] == '>') ? 1 : 3;
  str[i] = ' ';
  if (str[i] != '\0' && (str[i + 1] == '>' || str[i + 1] == '<'))
    *k = *k + 1;
  if (str[i] != '\0' && (str[i + 1] == '>' || str[i + 1] == '<'))
    i = i + 1;
  str[i] = ' ';
  while (str[++i] && str[i] == ' ');
  j = i;
  while (str[i] && str[i++] != ' ');
  if ((redirect = malloc(sizeof(char*) * (i - j + 1))) == NULL)
    exit(0);
  i = 0;
  while (str[j] && str[j] != ' ')
    {
      redirect[i++] = str[j];
      str[j++] = ' ';
    }
  redirect[i] = '\0';
  return (redirect);
}

int	check_redirections_syntax(char *str, int *l)
{
  int	i;
  int	k;

  *l = 0;
  i = -1;
  while (str[++i])
    {
      if (str[i] == '>' || str[i] == '<')
	{
	  if (str[i + 1] == '>' || str[i + 1] == '<')
	    i = i + 1;
	  if (str[i + 1] == '>' || str[i + 1] == '<')
	    return (-1);
	  while (str[++i] && str[i] == ' ');
	  k = i;
	  while (str[++k])
	    if (str[k] == '<' || str[k] == '>')
	      return (-1);
	}
    }
  return (1);
}

int	check_second_redirections_syntax(char *str, int *j)
{
  int	i;

  *j = 1;
  i = -1;
  while (str[++i] && str[i] == ' ');
  if (str[i] != '>' && str[i] != '<')
    return (-1);
  i = i + 1;
  if (str[i] == '>' || str[i] == '<')
    i = i + 1;
  if (str[i] == '>' || str[i] == '<')
    return (-1);
  while (str[i] && str[i] != '>' && str[i] != '<'  && str[i] == ' ')
    i = i + 1;
  while (str[i] && str[i] != '>' && str[i] != '<' && str[i++] != ' ')
    i = i + 1;
  while (str[i] && str[i] != '>' && str[i] != '<' && str[i++] == ' ')
    i = i + 1;
  if (check_str_space(str, i) == 1 || str[i] == '>' || str[i] == '<')
    return (-1);
  return (1);
}

char	*check_second_redirections(char *str, int *j)
{
  int	i;
  int	k;
  char	*redirect;

  i = -1;
  while (str[++i] && str[i] == ' ');
  str[i] = ' ';
  *j = (str[i] == '>') ? 1 : 3;
  *j = (str[i + 1] == '>' || str[i + 1] == '<') ? *j + 1 : *j;
  i = (str[i + 1] == '>' || str[i + 1] == '<') ? i + 1  : i;
  while (str[++i] && str[i] == ' ');
  k = i;
  while (str[i] && str[i] != ' ')
    i = i + 1;
  if ((redirect = malloc(sizeof(char*) * (i - k + 1))) == NULL)
    exit(0);
  i = -1;
  while (str[k] && str[k] != ' ')
    {
      redirect[++i] = str[k];
      str[k++] = ' ';
    }
  redirect[i + 1] = '\0';
  return (redirect);
}

char	*clear_redirects(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '>' || str[i] == '<')
	str[i] = ' ';
      i = i + 1;
    }
  return (str);
}
