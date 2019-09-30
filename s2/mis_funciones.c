#include "mis_funciones.h"

unsigned int char2int(char c) {
	
	return (c - '0');
}

int mi_atoi(char *s) {
    
	if (s != NULL) {
	
		int suma=0;;
        
		int i=0;
		if(s[i] == '-') i++;

		for (;i<strlen(s);i++) {
        
			suma *= 10;
			suma += char2int(s[i]);
		}
		if(s[0] == '-') return -suma;
		return suma;
	}
	return 0;
}

int esNumero(char *str){

	if(str != NULL){

		int i=0;
		if(str[i]=='-') ++str;
		for(; str[i]!='\0'; ++i){

			if(str[i]<'0' ||  str[i]>'9') return 0;

		}
		if (i>0 && i<= 8) return 1 ;
	}
	else return 0;
}
