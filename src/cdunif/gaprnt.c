#include <stdlib.h>
#include "grads.h"
/*---
  dump this routine defined in gauser.c but needed for linking by the GrADS routines
---*/

static char *datad = "/usr/local/lib/grads";

void gaprnt (int i, char *ch) {
  printf ("%s",ch);
}

/* Query env symbol */

char *gxgsym(char *ch) {
  return (getenv(ch));
}

gadouble qcachesf(void) {
  return(1.0);
}

void set_nc_cache(size_t arg) {
  return;
}

/* Construct full file path name from env symbol or default */

char *gxgnam(char *ch) {
char *fname, *ddir;
gaint len,i,j;
size_t sz;

  /* calc partial length of output string */
  len = 0;
  i = 0;
  while (*(ch+i)) { i++; len++;}

  /* Query the env symbol */
  ddir = gxgsym("GADDIR");

  /* calc the total length of the output string */
  if (ddir==NULL) {
    i = 0;
    while (*(datad+i)) { i++; len++;}
  } else {
    i = 0;
    while (*(ddir+i)) { i++; len++;}
  }

  /* Allocate memory for the output */
  sz = len+15;
  fname = (char *)galloc(sz,"fname");
  if (fname==NULL) {
    printf ("Memory allocation error in data set open\n");
    return (NULL);
  }

  /* fill in the directory depending on the value of the env var */
  if (ddir==NULL) {
    i = 0;
    while (*(datad+i)) {
      *(fname+i) = *(datad+i);
      i++;
    }
  } else if (*ddir=='.') {
    i = 0;
  } else {
    i = 0;
    while (*(ddir+i)) {
      *(fname+i) = *(ddir+i);
      i++;
    }
  }

  /* Insure a slash between dir name and file name */
  if (i!=0 && *(fname+i-1)!='/') {
    *(fname+i) = '/';
    i++;
  }

  /* fill in the file name */
  j = 0;
  while (*(ch+j)) {
    *(fname+i) = *(ch+j);
    i++; j++;
  }
  *(fname+i) = '\0';

  return (fname);
}


