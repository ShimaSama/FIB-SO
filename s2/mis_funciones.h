#ifndef MIS_FUNCIONES_H
# define MIS_FUNCIONES_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int esNumero(char *str);
/*
	Pre:	Cierto
	Post:	La funcion devuelve 1 si el string representa un numero y tiene como mucho 8 cifras y 0 en cualquier otro caso.
*/

unsigned int char2int(char c);
/*
	Pre:	c es un char. '0'>=c<='0'.
	Post:	Devuelve el carácter convertido a int.
*/

int mi_atoi(char *s);
/*
	Pre:	cierto.
	Post:	Devuelve un string convertido a int.
*/

#endif
