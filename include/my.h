/*
** my.h for h in /home/manass_j/rendu/Piscine_C_J09/include
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Oct  8 10:00:22 2015 jonathan manassen
** Last update Fri Jun  3 22:19:52 2016 jonathan manassen
*/

#ifndef MY_H_
# define MY_H_

typedef struct	s_prog
{
  int		i;
  int		j;
  int		k;
  char		c;
  int		*pfd;
  int		error[2];
  char		**path;
  char		*redirect;
  int		*value;
  int		fd;
  int		fd2[2];
  int		work;
  char		**p;
  int		quit;
}		t_prog;

typedef	struct	s_shrc
{
  char		**history;
  char		**alias;
  char		**set;
}		t_shrc;

void	my_putchar(char);
void	my_putnbr(int);
void	my_putnbr_u(unsigned int);
void	my_putstr(char*);
int	my_strlen(char*);
int	my_strlen_double_array(char**);
int	my_getnbr(char*);
int	my_printf(const char*, ...);
int	base(int, int);
int	intlen2(char, int, int);
void	my_fputchar(int, char);
int	my_fputnbr(int, int);
int	my_fputstr(int, char*);
int	my_fprintf(int, const char*, ...);
char	*get_next_line(const int);
int	check_str_space(char*, int);

#endif /* !MY_H_ */
