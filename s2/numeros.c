#include <unistd.h>



int esNumero(char *str){

	if(str != NULL){

		int i;
		if(str[i]=='-') ++str;
		for(; str[i]!='\0'; ++i){

			if(str[i]<'0' ||  str[i]>'9') return 0;

		}
		if (i>0 && i<= 8) return 1 ;

	}
	else return 0;
}


int main(int argc, char *argv[]){

	for(int i=0; i<argc; i++){
		if(esNumero(argv[i])) write(1, "ES UN NUMERO\n", 13);
		else write(1, "NO ES UN NUMERO\n", 16);


	}

}
