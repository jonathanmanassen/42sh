/*
** usual_get_next_line.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 08:40:21 2016 jonathan manassen
** Last update Sat Jun  4 17:37:30 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include "./include/get_next_line.h"
#include "my.h"

char	*my_realloc(char *str)
{
  char	*strr;
  int	i;
  int	size;

  i = 0;
  while (str[i])
    i = i + 1;
  size = READ_SIZE + i + 1;
  if ((strr = malloc(sizeof(char*) * size)) == NULL)
    return (NULL);
  i = 0;
  while (str[i])
    {
      strr[i] = str[i];
      i = i + 1;
    }
  strr[i] = 0;
  free(str);
  return (strr);
}

int	check_re(t_gnl *d)
{
  d->i = 0;
  while (d->re[d->i])
    {
      d->str[d->i] = d->re[d->i];
      d->i = d->i + 1;
    }
  d->str[d->i] = 0;
  d->i = 0;
  d->j = 0;
  while (d->str[d->j])
    {
      if (d->str[d->j] == '\n')
	{
	  d->str[d->j] = 0;
	  d->j = d->j + 1;
	  while (d->i < READ_SIZE)
	    d->re[d->i++] = d->str[d->j++];
	  d->re[d->i] = 0;
	  d->i = -1;
	  return (1);
	}
      d->j = d->j + 1;
    }
  d->i = -1;
  return (0);
}

int	check_read(t_gnl *d, int fd)
{
  d->i = 0;
  if ((d->ret = read(fd, d->buffer, READ_SIZE)) == 0)
    {
      if (d->str[0] == 0)
	{
	  free(d->str);
	  return (1);
	}
      else
	{
	  d->re[0] = 0;
	  d->re[1] = 0;
	  return (2);
	}
    }
  else if (d->ret < READ_SIZE && d->buffer[d->ret - 1] != '\n')
    {
      d->buffer[d->ret] = '\n';
      d->buffer[d->ret + 1] = 0;
    }
  else
    d->buffer[d->ret] = 0;
  d->i = 0;
  return (0);
}

int	check_str(t_gnl *d)
{
  while (d->buffer[d->i])
    {
      d->str[d->j] = d->buffer[d->i];
      if (d->buffer[d->i] == '\n')
	{
	  if (d->buffer[0] == '\n')
	    d->str[d->j] = 0;
	  d->str[d->j] = 0;
	  d->i = d->i + 1;
	  d->j = 0;
	  while (d->buffer[d->i])
	    {
	      d->re[d->j] = d->buffer[d->i++];
	      d->j = d->j + 1;
	    }
	  d->re[d->j] = 0;
	  d->i = -1;
	  return (1);
	}
      d->i = d->i + 1;
      d->j = d->j + 1;
    }
  d->str[d->j] = 0;
  d->str = my_realloc(d->str);
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	re[READ_SIZE + 1];
  t_gnl		d;

  if ((d.str = malloc(sizeof(char*) * READ_SIZE + 1)) == NULL)
    return (NULL);
  d.i = -1;
  while (++d.i < READ_SIZE + 1)
    d.re[d.i] = re[d.i];
  if ((d.t = check_re(&d)) == 1)
    while (++d.i < READ_SIZE + 1)
      re[d.i] = d.re[d.i];
  if (d.t == 1)
    return (d.str);
  while (1)
    {
      if ((d.s = check_read(&d, fd)) > 0)
	(d.s == 2) ? re[0] = 0 : 0;
      if (d.s > 0)
	return ((d.s == 2) ? d.str : NULL);
      if ((d.t = check_str(&d)) == 1)
	while (++d.i < READ_SIZE + 1)
	  re[d.i] = d.re[d.i];
      if (d.t == 1)
	return (d.str);
    }
}
