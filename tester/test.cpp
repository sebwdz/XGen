
#include	<cstdlib>
#include	<cstdio>
#include	<iostream>

int	**tab = NULL;

void	bcl(int x, int length, int val)
{
  if (!tab[x])
    tab[x] = new int[length];
  for (int it = 0; it < length; it++)
    {
      tab[x][it] = val;
      //std::cout << x << " " << it << std::endl;
    }
}

int	main()
{
  int	length = 1000;
  int	val = 5;

  tab = new int*[length];
  for (int it = 0; it < length; it++)
    tab[it] = NULL;
  for (int it = 0; it < length; it++)
    bcl(it, length, val);
}
