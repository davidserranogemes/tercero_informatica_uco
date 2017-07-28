%{

int usuario=0;
char* user_name;
char* fecha;

void buscar_usuario(char * line);
%}

usuario [a-z|A-Z|-|_|0-9]+
fecha [0-9]?[0-9]\/[0-9]?[0-9]\/[0-9]{4}
hora [0-9]?[0-9]:[0-9][0-9]

%%
{usuario}[ ]{fecha} {buscar_usuario(yytext);}
.|\n ;


%%

void main(int argc, char* argv[]){
	int check=1;
	switch(argc){
		case 3:
			yyin=fopen(argv[1],"r");
			user_name=argv[2];
			fecha=NULL;
			break;
		case 4:
			yyin=fopen(argv[1],"r");
			user_name=argv[2];
			fecha=argv[3];
			break;
		default:
			printf("Error de sintaxis.\nSe debe escribir: ./ejercicio6.exe fichero nombre_usuario <fecha>\nFecha es un parametro opcional.\n");
			check=0;
			break;
	}		
	if(check){
		yylex();
		if(argc==3){
			printf("Se ha encontrado al usuario %s %d veces.\n",user_name,usuario);
		}else{
			printf("Se ha encontrado al usuario %s el día %s %d veces.\n",user_name,fecha,usuario);
	
		}
	}
}

void buscar_usuario(char* line){
	char * check_name;
	char * check_fecha;
	if(fecha!=NULL){
		check_name=strstr(line, user_name);
		check_fecha=strstr(line, fecha);
		if(check_name!=NULL && check_fecha!=NULL){
			usuario++;
		}
	}else{
		check_name=strstr(line, user_name);
		if(check_name!=NULL){
			usuario++;
		}
	}
}