/*
** my_getnbr.c for my_getnbr in /home/manass_j/rendu/Piscine_C_J07
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue Oct  6 10:11:43 2015 jonathan manassen
** Last update Tue May 17 16:26:14 2016 jonathan manassen
*/

int	get_number(char *str, int i, int neg)
{
  int	nb;
  int	save;

  nb = 0;
  while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
      save = nb;
      if (save > (nb * 10 + (str[i] - '0')))
	return (0);
      nb = nb * 10 + (str[i++] - '0');
    }
  if (neg % 2 == 1)
    nb = nb * -1;
  return (nb);
}

int	my_getnbr(char *str)
{
  int	i;
  int	nb;
  int	neg;

  i = 0;
  neg = 0;
  while (str[i])
    {
      if (str[i] == '-')
	neg = neg + 1;
      if (str[i] >= '0' && str[i] <= '9')
	{
	  nb = get_number(str, i, neg);
	  return (nb);
	}
      i = i + 1;
    }
  return (0);
}
