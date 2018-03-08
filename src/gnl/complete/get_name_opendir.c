/*
** get_name_opendir.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon May 23 15:23:36 2016 jonathan manassen
** Last update Sat Jun  4 19:19:01 2016 jonathan manassen
*/

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
#include "my.h"
#include "./include/complete.h"

char	**get_ls(char **str, char *get_name, DIR *dirp, int i)
{
  struct stat	sb;
  struct dirent *d;
  int	j;
  int	k;

  while ((d = readdir(dirp)) != NULL)
    if (d->d_name[0] != '.')
      {
	j = my_strlen(d->d_name) + 2;
	if ((str[i] = malloc(sizeof(char*) * j)) == NULL)
	  exit(0);
	str[i] = d->d_name;
	j = my_strlen(d->d_name);
	k = my_strlen(get_name);
	while (--k > 0 && get_name[k] != ' ' && get_name[k] != '/');
	k = (k < 0) ? 0 : k;
	k = (get_name[k] == ' ' || get_name[k] == '/') ? k + 1 : k;
	if (stat(change_str_for_stat(d->d_name, get_name, k), &sb) != -1)
	  if (S_ISDIR(sb.st_mode))
	    str[i][j++] = '/';
	str[i][j] = '\0';
	i = i + 1;
      }
  str[i] = NULL;
  return (str);
}

char	*get_name_opendir_current(char *str, int *k)
{
  *k = 2;
  if ((str = malloc(sizeof(char*) * 2)) == NULL)
    exit(0);
  str[0] = '.';
  str[1] = '\0';
  return (str);
}

char	*get_name_opendir_second(char *str, int *k)
{
  int	i;
  int	j;
  int	end;
  char	*name;

  *k = 1;
  if ((name = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  name[0] = '\0';
  j = i = -1;
  while (str[++i])
    j = (str[i] == '/') ? j + 1 : j;
  if (++j >= 1)
    {
      i = my_strlen(str);
      while (--i && str[i] != '/');
      end = i + 1;
      while (i >= 0 && str[i] != ' ')
	i = i - 1;
      j = -1;
      while (str[++i] && i < end)
	name[++j] = str[i];
      name[j + 1] = '\0';
    }
  return (name);
}

char	*get_name_opendir(char *str, int *k)
{
  int	i;
  int	j;
  char	*name;

  *k = 0;
  if ((name = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  name[0] = '\0';
  i = j = 0;
  while (str[i])
    {
      if (str[i] == '/')
	j = j + 1;
      i = i + 1;
    }
  if (j >= 1)
    {
      i = my_strlen(str);
      while (--i >= 0 && str[i] != ' ');
      j = -1;
      while (str[++i])
	name[++j] = str[i];
      name[j + 1] = '\0';
    }
  return (name);
}
