#include <stdio.h>
#include <time.h>


int fiit ( int n) { 
	int i, f, g, h;
	i=0;
	f=1;
	h=1;
	for (i=2 ; i<=n; i++){
		g = f+h;
		f=h;
		h=g;
	}
	return h;
}
	

int firecu ( int n) { 
	if (n < 2)
		return n;
	else
		return firecu(n-1) + firecu(n-2);
}


typedef unsigned long long int ullint;

struct paire {
	ullint fun;
	ullint fdeux;
};
typedef struct paire paire;

paire fiblog (int n) {
  paire mi, res;
  ullint fi;
  int i;
  main()
  if (n < 2) {
	res.fun = (ullint) 1;
	res.fdeux = (ullint) 1;
	return res;
  }
  i = n >> 1;
  mi = fiblog(i);
  if (n & 0x01) {
	res.fdeux = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
	res.fun = (mi.fun + mi.fdeux + mi.fdeux) * mi.fun;
	return res;
  }
  res.fun = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
  res.fdeux = (mi.fun + mi.fun - mi.fdeux) * mi.fdeux;
  return res;
}
ullint fibo (int n) {
  paire res;
  if (n >= 0 && n < 92) {
	res = fiblog (n);
	return res.fun;
  }
  return (ullint) 0;
}



int main (){
	clock_t a = clock();
	fiblog(10000000);

	clock_t b = clock();	
	clock_t end = (double)(b - a);

	printf ("%f \n", (double)end);
	return 0;
}