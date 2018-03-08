/*
** my_put_nbr.c for my_put_nbr in /home/manass_j/day03
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Wed Sep 30 13:32:31 2015 jonathan manassen
** Last update Thu Apr 28 14:51:39 2016 jonathan manassen
*/

#include "../../include/my.h"

void	my_putnbr(int nb)
{
  int	mod;

  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * (-1);
    }
  if (nb >= 0)
    {
      if (nb >= 10)
	{
	  mod = (nb % 10);
	  nb = (nb - mod) / 10;
	  my_putnbr(nb);
	  my_putchar(48 + mod);
	}
      else
	my_putchar(48 + nb % 10);
    }
}

void	my_putnbr_u(unsigned int nb)
{
  int	mod;

  if (nb >= 10)
    {
      mod = (nb % 10);
      nb = (nb - mod) / 10;
      my_putnbr(nb);
      my_putchar(48 + mod);
    }
  else
    my_putchar(48 + nb % 10);
}
