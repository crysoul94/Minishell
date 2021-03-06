#include "minishell.h"

/* 1 - Commande CHDIR */

void		cd_dir(char *path)
{
  int	a;
  
  a = chdir(path);
  if (a == -1)
  my_putstr("Bash : Aucun dossier de ce type");
}

/* Exit */
int		exit_prog(char *str)
{
  int	i;
  
  i = 0;
  if (str[0] == 'e' && str[1] == 'x')
    i++;
  if (str[2] == 'i' && str[3] == 't')
    i++;
  return (i);
}

/* 3 - Découpe l'input user + exit */

char		**get_command()
{
  char	*cmd;
  char	**tab;
  int	pid;
  
  cmd = get_line(0);
  if (cmd[0] != '\0')
    {
      tab = rb_str_to_wordtab(cmd, ' ');
      if (exit_prog(tab[0]) == 2)
	{
	  pid = getpid();
	  kill(pid,SIGKILL);
	  exit(0);
	}  
    }
  return (tab);
}
  
/* 4 - Loop du minishell */

int		main(int ac, char **av, char **env)
{
  char	**tab;
  char	**path;
  char	*cmd;
  
  welcome();
  while (42)
    {
      prompt();
      tab = get_command();
      if (tab[0][0] == 'c' && tab[0][1] == 'd')
	cd_dir(tab[1]);
      else
	{
	  path = my_getenv(env);
	  cmd = find_path(path,tab[0]);
	  tab[0] = cmd;
	  exec_cmd(cmd, tab ,env);
	  wait(NULL);
	}
    }
  return (0);
}
  
