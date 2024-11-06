#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdbool.h> 
#include "analex.h" 
#define TAM_LEXEMA 50 
#define TAM_NUM 20 

void error(char msg[]) { 
	printf("%s Linha: %d\n", msg, contLinha);
	exit(1);
} 

int verificarPVR(char pv_reservadas[][28] , char string[]){
	int i;
    for(i = 0 ; i < 28 ; i++){
        if(strcmp(pv_reservadas[i] , string) == 0){
          return i;
        }
    }

    return -1;
}

TOKEN AnaLex(FILE *fd){
	 int estado = 0;
	 char lexema[TAM_LEXEMA] = "";
	 int tamL = 0;
	 char digitos[TAM_NUM] = "";
	 int tamD = 0;
	 TOKEN t;

	 
	 char pv_reservadas[28][28] = {"const", "pr", "init", "endp", "char", "real", "int", "bool", "do", "while", 
	 "endw", "var", "from", "dt", "to", "by", "if", "endv", "elif", "else", "endi", "getout", "putreal", "getint", "getreal", "getchar", "putint", "putchar"};
	 
	 while(1)
	 {
		 char c = fgetc(fd);
		 switch(estado)
		 {
		 	 case 0:
		 	 	if(c == ' ' || c == '\t') 
				{
					estado = 0;
				}  
		 	 	else if(c == '_')
			    {
					estado = 2;
					lexema[tamL] = c;
					lexema[++tamL] = '\0';
				}
				else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
				{
					estado = 1;
					lexema[tamL] = c;
					lexema[++tamL] = '\0';
				}
				else if(c >= '0' && c <= '9')
				{
					estado = 4;
					digitos[tamD] = c;
					digitos[++tamD] = '\0';
				}
				else if(c == '\'')
				{
					estado = 8;
				}
				else if(c == '\"')
				{
					estado = 15;
				}
				else if(c == '/')
				{
					estado = 20;
				}
				else if(c == '+')
				{
					estado = 22;
					t.cat = SN;
					t.codigo = ADI;
					return t;
				}
				else if(c == '-')
				{
					estado = 23;
					t.cat = SN;
					t.codigo = SUB;
					return t;
				}
				else if(c == '*')
				{
					estado = 24;
					t.cat = SN;
					t.codigo = MUL;
					return t;
				}
				else if(c == '&')
				{
					estado = 25;
				}
				else if(c == '|')
				{
					estado = 28;
				}
				else if(c == '>')
				{
					estado = 30;
				}
				else if(c == '<')
				{
					estado = 33;
				}
				else if(c == '=')
				{
					estado = 36;
				}
				else if(c == '!')
				{
					estado = 39;
				}
				else if(c == '(')
				{
					estado = 42;
					t.cat = SN;
					t.codigo = APAR;
					return t;
				}
				else if(c == ')')
				{
					estado = 43;
					t.cat = SN;
					t.codigo = FPAR;
					return t;
				}
				else if(c == '[')
				{
					estado = 44;
					t.cat = SN;
					t.codigo = ACOL;
					return t;
				}
				else if(c == ']')
				{
					estado = 45;
					t.cat = SN;
					t.codigo = FCOL;
					return t;
				}
				else if(c == ',')
				{
					estado = 46;
					t.cat = SN;
					t.codigo = VIRG;
					return t;
				}
				else if(c == '{')
				{
					estado = 47;
					t.cat = SN;
					t.codigo = ACH;
					return t;
				}
				else if(c == '}')
				{
					estado = 48;
					t.cat = SN;
					t.codigo = FCH;
					return t;
				}
				else if(c == '\n')
				{
					contLinha++;
				}
				else if(c == EOF)
				{
					t.cat = FA;
					return t;
				}
				else
				{
					error("caracter invalido!");
				}
			 break;
	 	 	 case 1:
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || ((c >= '0') && (c <= '9')))
				{
					estado = 1;
					lexema[tamL] = c;
					lexema[++tamL] = '\0'; 
				}
				else
				{
					estado = 3; //identificador
					ungetc(c, fd);
					
					if((verificarPVR(pv_reservadas, lexema) != -1))
					{
						t.cat = PVR;
                    } 
					else
					{
                        t.cat = ID; 
                    }

					strcpy(t.lexema,lexema);
					return t;
				}
			 break;
	 	 	 case 2:
	 	 	 	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
				{
					estado = 1;
					lexema[tamL] = c;
					lexema[++tamL] = '\0';   	
				}
				else
				{
					error("caracter invalido!");
				}
		     break;
   		 	 case 4:
   		 	 	if(c >= '0' && c <= '9')
				{
					estado = 4;
					digitos[tamD] = c;
					digitos[++tamD] = '\0';	
				}
				else if(c == '.')
				{
					estado = 6;
					digitos[tamD] = c;
					digitos[++tamD] = '\0';
				}
				else
				{
					estado = 5; //const int
					ungetc(c, fd);
					t.cat = CT_I;
					t.valInt = atoi(digitos);
					return t;
				}
	 	 	 break;
	 	     case 6:
	 	     	if(c >= '0' && c <= '9')
			   {
			   		estado = 49;
			   		digitos[tamD] = c;
					digitos[++tamD] = '\0';	
			   }
			   else
			   {
				   error("caracter invalido!");
			   }
			 break;
		 	 case 49:
		 	 	if(c >= '0' && c <= '9')
				{
				  	estado = 49;
			   		digitos[tamD] = c;
					digitos[++tamD] = '\0';
				}
	   			else
			   {
				   estado = 7; //const real
				   ungetc(c, fd);
				   t.cat = CT_R;
				   t.valReal = atof(digitos);
				   return t;
			   }
	 	 	 break;
  	  	     case 8:
  	  	     	if((isprint(c) != 0) && (c != '\\') && (c != '\''))
				{
				  	estado = 9;
				  	lexema[tamL] = c;
				  	lexema[++tamL] = '\0';
				}
				else if(c == '\\')
				{
					 estado = 10;
					 lexema[tamL] = c;
				   	 lexema[++tamL] = '\0';
				}
				else
			   {
				   error("caracter invalido!");
			   }
			 break;
		 	 case 9:
		 	 	if(c == '\'')
				{
					estado = 13; //const char
					t.cat = CT_C;
					t.c = lexema[--tamL];
					return t;
				}
				else
			    {
				    error("caracter invalido!");
			    }
 		     break;
 		 	 case 10:
 		 	 	if(c == 'n')
			    {
			   		estado = 11;
			   		lexema[tamL] = c;
					lexema[++tamL] = '\0';
			    }
			    else if(c == '0')
				{
					estado = 12;
			   		lexema[tamL] = c;
					lexema[++tamL] = '\0';
				}
				else
			    {
				    error("caracter invalido!");
			    }
 		 	 break;
   		 	 case 11:
   		 	 	if(c == '\'')
				{
					estado = 13; //const char
					t.cat = CT_C;
					t.c = '\n';
					return t;
				}
				else
			    {
				    error("caracter invalido!");
			    }
   		 	 break;
   		  	 case 12:
   		 	 	if(c == '\'')
				{
					estado = 13; //const char
					t.cat = CT_C;
					t.c = '\0';
					return t;
				}
				else
			    {
				    error("caracter invalido!");
			    }
   		 	 break;
		 	 case 15:
			 	if((isprint(c) != 0) && (c != '"') && (c != '\n'))
				{
				 	estado = 15;
				 	lexema[tamL] = c;
					lexema[++tamL] = '\0';
				}
				else if(c == '"')
				{
					estado = 16; //literal
					t.cat = LT;
					strcpy(t.lexema, lexema);
					return t;
				}
				else
			    {
				    error("caracter invalido!");
			    }
			 break;
		 	 case 20:
		 	 	if(c == '/')
				{
					estado = 17;
				}
				else
				{
					estado = 21; //sinal divisão
					ungetc(c, fd);
					t.cat = SN;
					t.codigo = DIV;
					return t;
				}
			 break;
		 	 case 17:
		 	 	if((isprint(c) != 0) && (c != '\n'))
				{
					//printf("caracter");
					estado = 17;
				}
				else if(c == '\n')
				{
					contLinha++;
					estado = 0;
				}
				else if(c == EOF)
				{
					t.cat = FA;
					return t;
				}
				else
				{
					error("caracter invalido!");
				}
			 break;
		 	 case 25:
		 	 	if(c == '&')
				{
					estado = 26; //sinal and
					t.cat = SN;
					t.codigo = AND;
					return t;
				}
				else
				{
					estado = 27; //sinal endereço
					ungetc(c, fd);
					t.cat = SN;
					t.codigo = EN;
					return t;
				}
		 	 break;
  			 case 28:
  			 	if(c == '|')
				{
					estado = 29;
					t.cat = SN;
					t.codigo = OU;
					return t;
				}
				else
				{
					error("caracter invalido!");
				}
		 	 break;
			 case 30:
			 	if(c == '=')
				{
					estado = 31;
					t.cat = SN;
					t.codigo = MAIQ;
					return t;
				}
				else
				{
					estado = 32;
					t.cat = SN;
					t.codigo = MAQ;
					return t;
				}
			 break;
		 	 case 33:
			 	if(c == '=')
				{
					estado = 35;
					t.cat = SN;
					t.codigo = MEIQ;
					return t;
				}
				else
				{
					estado = 34;
					t.cat = SN;
					t.codigo = MEQ;
					return t;
				}
			 break;
		 	 case 36:
		 	 	if(c == '=')
				{
					estado = 37;
					t.cat = SN;
					t.codigo = COMP;
					return t;
				}
				else
				{
					estado = 38;
					t.cat = SN;
					t.codigo = ATRIB;
					return t;
				}
			 break;
		 	 case 39:
		 	 	if(c == '=')
				{
					estado = 41;
					t.cat = SN;
					t.codigo = DIF;
					return t;
				}
				else
				{
					estado = 40;
					t.cat = SN;
					t.codigo = NEG;
					return t;
				}
			 break;
		 default:
			 break;
		 }
	 }
 }

 int main(int argc, char** argv)
 {
	 //proc
	FILE *f;
	TOKEN tk;
	if ((f = fopen("test.txt", "r")) == NULL)
		exit(1);
	while (1)
	{
		tk = AnaLex(f);
		switch (tk.cat)
		{
		case SN:
			switch (tk.codigo)
			{
			case ADI:
				printf("<SN, ADI>\n");
				break ;
			case MUL:
				printf("<SN, MUL>\n");
				break ;

			case SUB:
				printf("<SN, SUB>\n");
				break ;

			case DIV:
				printf("<SN, DIV>\n");
				break ;

			case MAQ:
				printf("<SN, MAQ>\n");
				break ;

			case MAIQ:
				printf("<SN, MAIQ>\n");
				break ;

			case MEQ:
				printf("<SN, MEQ>\n");
				break ;

			case MEIQ:
				printf("<SN, MEIQ>\n");
				break ;

			case ATRIB:
				printf("<SN, ATRIB>\n");
				break ;

			case COMP:
				printf("<SN, COMP>\n");
				break ;

			case APAR:
				printf("<SN, APAR>\n");
				break ;

			case FPAR:
				printf("<SN, FPAR>\n");
				break ;

			case ACOL:
				printf("<SN, ACOL>\n");
				break ;

			case FCOL:
				printf("<SN, FCOL>\n");
				break ;

			case OU:
				printf("<SN, OU>\n");
				break ;

			case EN:
				printf("<SN, EN>\n");
				break ;

			case AND:
				printf("<SN, AND>\n");
				break ;

			case NEG:
				printf("<SN, NEG>\n");
				break ;

			case DIF:
				printf("<SN, DIF>\n");
				break ;

			case VIRG:
				printf("<SN, VIRG>\n");
				break ;

			case ACH:
				printf("<SN, ACH>\n");
				break ;
			case FCH:
				printf("<SN, FCH>\n");
				break ;
			}
			break ;
		case PVR:
			printf("<PVR, %s> \n", tk.lexema);
			break ;
		case ID:
			printf("<ID, %s>\n", tk.lexema);
			break ;
		case CT_I:
			printf("<CT_I, %d>\n", tk.valInt);
			break ;
		case CT_R:
			printf("<CT_R, %f>\n", tk.valReal);
			break ;
		case CT_C:
			printf("<CT_C, %c> \n", tk.c);
			break ;
		case LT:
			printf("<LT, %s> \n", tk.lexema);
			break ;
		case FA:
			printf("<FA, EOF>");
			break ;
		}
		if (tk.cat == FA)
			break ;
	}
	fclose(f);
	 
	 return 0;
 }