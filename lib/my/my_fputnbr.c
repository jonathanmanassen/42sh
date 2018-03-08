/*
** my_put_nbr.c for d3ex7 in /home/mei_c/rendu/Piscine_C_J03
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Wed Sep 30 17:55:36 2015 christophe mei
** Last update Sat Apr  2 17:12:58 2016 christophe mei
*/

#include "my.h"

int     floopbr(int fd, int i, int nbstart, int nb)
{
  if (nb < 0)
    {
      my_fputchar(fd, '-');
      nbstart = nbstart * -1;
      nb = nb * -1;
    }
  while (nb / i > 9)
    {
      i = i * 10;
    }
  while (i >= 1)
    {
      nb = nbstart / i;
      nb = nb - nb / 10 * 10;
      i = i / 10;
      my_fputchar(fd, nb + 48);
    }
  return (0);
}

int	my_fputnbr(int fd, int nb)
{
  int	i;
  int	nbstart;

  i = 1;
  nbstart = nb;
  floopbr(fd, i, nbstart, nb);
  return (0);
}
