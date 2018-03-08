/*
** complete_word.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 06:15:03 2016 jonathan manassen
** Last update Sat Jun  4 18:40:57 2016 jonathan manassen
*/

#include <stdlib.h>
#include <ncurses/curses.h>
#include <dirent.h>
#include "my.h"
#include "./include/complete.h"

char		*try_complete(char *str, char **tab, int *k, int nb)
{
  int		i;
  int		j;
  int		*hide;
  t_coord	c;

  j = c.i = -1;
  if ((hide = malloc(sizeof(int*) * nb)) == NULL)
    exit(0);
  hide = get_hide(tab, str, hide, &c.k);
  while (++j < nb)
    {
      i = hidenp(tab[hide[0]], tab[hide[j]], 1);
      i = i - c.k - 1;
      if (i < -1 && c.i == -1)
	c.i = my_strlen(tab[hide[0]]) - 1;
      else if (c.i == -1 || (i < c.i && i >= -1))
	c.i = i;
    }
  if (c.i > 0)
    {
      *k = 1;
      str = get_part_of_word(str, tab, c, hide[0]);
      return (str);
    }
  return (str);
}

char	*launch_try_complete(char **tab, char *str, int *l, int *m)
{
  int	i;
  int	j;
  int	k;

  *l = -2;
  i = -1;
  j = 0;
  k = 0;
  while (tab[++i])
    if (hidenp(str, tab[i], 0) == -1)
      j = j + 1;
  *m = j;
  if (j == 0)
    *l = -1;
  if (j == 0)
    return (str);
  if (j > 1)
    str = try_complete(str, tab, &k, j);
  if (k > 0)
    {
      *l = my_strlen(str);
      return (str);
    }
  (j > 1) ? my_printf("\n\r") : 0;
  return (str);
}

void	show_ls(char **tab, char *str, int row, int k)
{
  int	j;
  int	i;
  int	col;

  j = row;
  col = 0;
  i = -1;
  while (tab[++i])
    if (hidenp(str, tab[i], 0) == -1)
      {
	if (j == row - (row - k))
	  {
	    if (col == 0)
	      my_printf("\r");
	    my_printf("%s", tab[i]);
	    col = 23 - my_strlen(tab[i]);
	    while (col < 0)
	      col = col + 23;
	    col = write_stat(tab[i], col);
	    while (col-- > 0)
	      my_printf(" ");
	    col = 1;
	  }
	j = (--j == 0) ? row : j;
      }
}

void	launch_write_ls(char **tab, char *str, int i, int j)
{
  int	k;
  int	row;
  int	col;

  getmaxyx(stdscr, row, col);
  row = 1;
  while (tab[++i])
    if (hidenp(str, tab[i], 0) == -1)
      {
	k = 23 - my_strlen(tab[i]);
	while (k < 0)
	  k = k + 23;
	j = j + k + my_strlen(tab[i]);
	if (j / row > col)
	  j = j + 23 - my_strlen(tab[i]);
	if (j / row > col)
	  row = row + 1;
      }
  j = row;
  while (row > 0)
    {
      show_ls(tab, str, j, row--);
      if (row > 0)
	my_printf("\n");
    }
}

char	*auto_complete(char *str, int *l, int *curpos)
{
  char	**tab;
  int	i;
  int	j;
  int	k;

  tab = no_options(count_files(str), str);
  str = launch_try_complete(tab, str, &k, &j);
  if (k >= 0)
    *l = *curpos = k;
  if (k >= -1)
    return (str);
  i = -1;
  while (tab[++i])
    if (hidenp(str, tab[i], 0) == -1 && j == 1)
      {
	str = get_word(str, i, tab, &j);
	*l = *curpos = j;
	return (str);
      }
  if (j > 1)
    launch_write_ls(tab, str, -1, 0);
  my_putchar('\n');
  return (str);
}
