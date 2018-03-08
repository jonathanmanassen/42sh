/*
** misc_get_next_line.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sun May 22 00:10:38 2016 jonathan manassen
** Last update Sun Jun  5 21:48:54 2016 jonathan manassen
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <curses.h>
#include <stdlib.h>
#include "my.h"
#include "./include/gnl_ncurses.h"

char	*my_realloc_ncurses(char *str)
{
  char	*dest;
  int	i;

  if ((dest = malloc(sizeof(char*) * (my_strlen(str) + 2))) == NULL)
    exit(0);
  i = 0;
  while (str[i])
    {
      dest[i] = str[i];
      i = i + 1;
    }
  dest[i] = '\0';
  free(str);
  return (dest);
}

int		hidenp(char *str, char *tab, int a)
{
  struct stat	sb;
  int		i;
  int		j;
  int		k;
  int		l;

  i = my_strlen(str);
  if (a == 1 && i - 1 > 0 && str[i - 1] == '/')
    i = i - 1;
  while (--i > 0 && str[i] != ' ' && (str[i] != '/'));
  i = (i < 0) ? 0 : i;
  if (str[i] == ' ' || str[i] == '/')
    i = i + 1;
  if (a == 0 && stat(change_str_for_stat(tab, str, i), &sb) == -1)
    return (EXIT_FAILURE);
  check_if_slash_space(str, &l, &k);
  if (a == 0 && !(sb.st_mode & S_IXUSR) && k >= 1 && l == 0)
    return (i);
  j = -1;
  --i;
  while (str[++i] && tab[++j])
    if (str[i] != tab[j])
      return (i);
  return ((str[i] != '\0') ? i : -1);
}

char	*put_char_in_str(char *str, char c, int *i, int *curpos)
{
  int	j;
  int	k;
  char	*tmp;

  j = -1;
  if ((tmp = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  while (++j < *curpos)
    tmp[j] = str[j];
  k = j;
  while (++j <= *i)
    tmp[j] = str[j - 1];
  tmp[k] = c;
  tmp[j] = '\0';
  *i = *i + 1;
  *curpos = *curpos + 1;
  return (tmp);
}

void	show_get_next_line(char *str, char **env, int fd, int curpos[2])
{
  int	i;

  if (fd == 0)
    {
      my_printf("\r\e[0J");
      show_prompt(env);
      my_printf("%s", str);
      i = curpos[0] - curpos[1];
      while (i-- > 0)
	my_putchar('\b');
    }
}

char	*init_get_next_line(int curpos[2], int *hist)
{
  char	*str;

  *hist = 0;
  curpos[1] = 0;
  curpos[0] = 0;
  if ((str = malloc(sizeof(char*) * 2)) == NULL)
    exit(0);
  noecho();
  str[0] = '\0';
  return (str);
}
